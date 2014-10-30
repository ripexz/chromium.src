// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_DOCUMENT_SCAN_MOCK_DOCUMENT_SCAN_INTERFACE_H_
#define CHROME_BROWSER_EXTENSIONS_API_DOCUMENT_SCAN_MOCK_DOCUMENT_SCAN_INTERFACE_H_

#include <string>

#include <gmock/gmock.h>

#include "chrome/browser/extensions/api/document_scan/document_scan_interface.h"

namespace extensions {

namespace api {

class MockDocumentScanInterface : public DocumentScanInterface {
 public:
  MockDocumentScanInterface();
  virtual ~MockDocumentScanInterface();

  MOCK_METHOD4(Scan, void(const std::string& scanner_name,
                          ScanMode mode,
                          int resolution_dpi,
                          const ScanResultsCallback& callback));
  MOCK_METHOD1(ListScanners, void(const ListScannersResultsCallback& callback));
  MOCK_CONST_METHOD0(GetImageMimeType, std::string());
};

}  // namespace api

}  // namespace extensions

#endif  // CHROME_BROWSER_EXTENSIONS_API_DOCUMENT_SCAN_MOCK_DOCUMENT_SCAN_INTERFACE_H_
