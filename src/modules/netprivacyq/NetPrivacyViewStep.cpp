/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2026 Bounty Contributors
 *   SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "NetPrivacyViewStep.h"
#include "Config.h"
#include "Branding.h"
#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/Logger.h"
#include "utils/Variant.h"

NetPrivacyViewStep::NetPrivacyViewStep( QObject* parent )
    : Calamares::QmlViewStep( parent )
    , m_config( new Config( this ) )
{
    emit nextStatusChanged( true );
}

QString NetPrivacyViewStep::prettyName() const
{
    return tr( "Network Privacy" );
}

bool NetPrivacyViewStep::isNextEnabled() const
{
    return m_config->isValid();
}

bool NetPrivacyViewStep::isBackEnabled() const
{
    return true;
}

QObject* NetPrivacyViewStep::getConfig()
{
    return m_config;
}

CALAMARES_PLUGIN_FACTORY_DEFINITION( NetPrivacyViewStepFactory, registerPlugin< NetPrivacyViewStep >(); )
