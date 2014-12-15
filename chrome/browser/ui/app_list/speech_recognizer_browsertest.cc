// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/ui/app_list/speech_recognizer.h"

#include "base/command_line.h"
#include "base/memory/weak_ptr.h"
#include "base/run_loop.h"
#include "base/strings/utf_string_conversions.h"
#include "base/threading/platform_thread.h"
#include "chrome/browser/ui/app_list/speech_recognizer_delegate.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/common/chrome_switches.h"
#include "chrome/test/base/in_process_browser_test.h"
#include "chrome/test/base/testing_profile.h"
#include "content/public/browser/browser_thread.h"
#include "content/public/test/fake_speech_recognition_manager.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

using ::testing::InvokeWithoutArgs;
using ::testing::Return;

namespace app_list {

class MockSpeechRecognizerDelegate : public SpeechRecognizerDelegate {
 public:
  MockSpeechRecognizerDelegate() : weak_factory_(this) {}

  base::WeakPtr<MockSpeechRecognizerDelegate> GetWeakPtr() {
    return weak_factory_.GetWeakPtr();
  }

  MOCK_METHOD2(OnSpeechResult, void(const base::string16&, bool));
  MOCK_METHOD1(OnSpeechSoundLevelChanged, void(int16_t));
  MOCK_METHOD1(OnSpeechRecognitionStateChanged, void(SpeechRecognitionState));
  MOCK_METHOD2(GetSpeechAuthParameters, void(std::string*, std::string*));

 private:
  base::WeakPtrFactory<MockSpeechRecognizerDelegate> weak_factory_;
};

class AppListSpeechRecognizerBrowserTest : public InProcessBrowserTest {
 public:
  AppListSpeechRecognizerBrowserTest() {}

  void SetUpOnMainThread() override {
    InProcessBrowserTest::SetUpOnMainThread();

    fake_speech_recognition_manager_.reset(
        new content::FakeSpeechRecognitionManager());
    fake_speech_recognition_manager_->set_should_send_fake_response(true);
    content::SpeechRecognitionManager::SetManagerForTesting(
        fake_speech_recognition_manager_.get());
    mock_speech_delegate_.reset(new MockSpeechRecognizerDelegate());
  }

  void TearDownOnMainThread() override {
    // Poor-person's way of ensuring IO loop is idle.
    auto io_loop = content::BrowserThread::UnsafeGetMessageLoopForThread(
        content::BrowserThread::IO);
    ASSERT_TRUE(io_loop);
    while (!io_loop->IsIdleForTesting()) {
      // Sleep for a little bit, allowing the IO thread to obtain any locks
      // taken by IsIdleForTesting(). Without this sleep, this loop may livelock
      // the message loop causing the test to fail.
      base::PlatformThread::Sleep(base::TimeDelta::FromMilliseconds(10));
    }
  }

 protected:
  scoped_ptr<content::FakeSpeechRecognitionManager>
      fake_speech_recognition_manager_;
  scoped_ptr<MockSpeechRecognizerDelegate> mock_speech_delegate_;

 private:
  DISALLOW_COPY_AND_ASSIGN(AppListSpeechRecognizerBrowserTest);
};

IN_PROC_BROWSER_TEST_F(AppListSpeechRecognizerBrowserTest, RecognizeSpeech) {
  SpeechRecognizer recognizer(mock_speech_delegate_->GetWeakPtr(),
                              browser()->profile()->GetRequestContext(),
                              "en");

  base::RunLoop run_loop;
  EXPECT_CALL(*mock_speech_delegate_,
              OnSpeechResult(base::ASCIIToUTF16("Pictures of the moon"), true));
  EXPECT_CALL(*mock_speech_delegate_,
              OnSpeechRecognitionStateChanged(SPEECH_RECOGNITION_READY))
      .WillOnce(InvokeWithoutArgs(&run_loop, &base::RunLoop::Quit));
  recognizer.Start();
  run_loop.Run();
}

}  // namespace app_list


