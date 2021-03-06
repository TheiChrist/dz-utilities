/*
* Project:   dzUtilities::Console
* Github:    https://github.com/tpiekarski/dzUtilities
* Copyright: (c) 2017-2018 Thomas Piekarski <t.piekarski@deloquencia.de>
* License:   Mozilla Public License, v. 2.0
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
*
*/

#ifndef H_CONSOLE_PROPERTIES_ACTION
#define H_CONSOLE_PROPERTIES_ACTION

#include "console_constants.h"
#include <dzaction.h>

class ConsoleSettingsAction : public DzAction {

  Q_OBJECT

public:
  ConsoleSettingsAction();
  ~ConsoleSettingsAction() = default;

protected:
  QString getActionGroup() const override { return CONSOLE_ACTION_GROUP; };
  void executeAction() override;

};

#endif

