// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_SCREENS_DEVICE_DISABLED_SCREEN_ACTOR_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_SCREENS_DEVICE_DISABLED_SCREEN_ACTOR_H_

namespace chromeos {

// Interface between the device disabled screen and its representation.
class DeviceDisabledScreenActor {
 public:
  // Allows the representation to access information about the screen.
  class Delegate {
   public:
    virtual ~Delegate() {
    }

    // Called when the actor is being destroyed. Note that if the Delegate is
    // destroyed first, it must call SetDelegate(nullptr).
    virtual void OnActorDestroyed(DeviceDisabledScreenActor* actor) = 0;
  };

  virtual ~DeviceDisabledScreenActor() {
  }

  virtual void Show() = 0;
  virtual void Hide() = 0;
  virtual void SetDelegate(Delegate* delegate) = 0;
};

}  // namespace chromeos

#endif  // CHROME_BROWSER_CHROMEOS_LOGIN_SCREENS_DEVICE_DISABLED_SCREEN_ACTOR_H_

