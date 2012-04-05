// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_SHELL_SHELL_RESOURCE_DISPATCHER_HOST_DELEGATE_H_
#define CONTENT_SHELL_SHELL_RESOURCE_DISPATCHER_HOST_DELEGATE_H_
#pragma once

#include "base/compiler_specific.h"
#include "content/public/browser/resource_dispatcher_host_delegate.h"

namespace content {

class ShellResourceDispatcherHostDelegate
    : public content::ResourceDispatcherHostDelegate {
 public:
  ShellResourceDispatcherHostDelegate();
  virtual ~ShellResourceDispatcherHostDelegate();

  // ResourceDispatcherHostDelegate implementation.
  virtual bool AcceptAuthRequest(net::URLRequest* request,
                                 net::AuthChallengeInfo* auth_info) OVERRIDE;
  virtual content::ResourceDispatcherHostLoginDelegate* CreateLoginDelegate(
      net::AuthChallengeInfo* auth_info, net::URLRequest* request) OVERRIDE;

 private:
  DISALLOW_COPY_AND_ASSIGN(ShellResourceDispatcherHostDelegate);
};

}  // namespace content

#endif  // CONTENT_SHELL_SHELL_RESOURCE_DISPATCHER_HOST_DELEGATE_H_
