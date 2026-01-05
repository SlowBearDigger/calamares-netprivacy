/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2026 Bounty Contributors
 *   SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef NETPRIVACYVIEWSTEP_H
#define NETPRIVACYVIEWSTEP_H

#include "Config.h"
#include "utils/PluginFactory.h"
#include "viewpages/QmlViewStep.h"
#include <DllMacro.h>
#include <QObject>

class PLUGINDLLEXPORT NetPrivacyViewStep : public Calamares::QmlViewStep
{
    Q_OBJECT

public:
    explicit NetPrivacyViewStep( QObject* parent = nullptr );
    QString prettyName() const override;
    bool isNextEnabled() const override;
    bool isBackEnabled() const override;
    QObject* getConfig() override;

private:
    Config* m_config;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( NetPrivacyViewStepFactory )

#endif
