// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_METRICS_METRICS_SERVICE_ACCESSOR_H_
#define CHROME_BROWSER_METRICS_METRICS_SERVICE_ACCESSOR_H_

#include <stdint.h>
#include <string>

#include "base/macros.h"

class MetricsService;
class MetricsServiceObserver;

// This class limits and documents access to metrics service helper methods.
// These methods are protected so each user has to inherit own program-specific
// specialization and enable access there by declaring friends.
class MetricsServiceAccessor {
 protected:
  // Constructor declared as protected to enable inheritance. Decendants should
  // disallow instantiation.
  MetricsServiceAccessor() {}

  // Registers/unregisters |observer| to receive MetricsLog notifications
  // from metrics service.
  static void AddMetricsServiceObserver(MetricsServiceObserver* observer);
  static void RemoveMetricsServiceObserver(MetricsServiceObserver* observer);

  // Registers the specified synthetic field trial (identified by a hash of the
  // trial name and group name) with |metrics_service|, if the service is not
  // NULL, returning true on success.
  // See the comment on MetricsService::RegisterSyntheticFieldTrial for details.
  static bool RegisterSyntheticFieldTrial(MetricsService* metrics_service,
                                          uint32_t trial_name_hash,
                                          uint32_t group_name_hash);

 private:
  DISALLOW_COPY_AND_ASSIGN(MetricsServiceAccessor);
};

#endif  // CHROME_BROWSER_METRICS_METRICS_SERVICE_ACCESSOR_H_
