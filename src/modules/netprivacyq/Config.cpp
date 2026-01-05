/* === This file is part of Calamares - <https://calamares.io> ===
 *   SPDX-FileCopyrightText: 2026 Bounty Contributors
 *   SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "Config.h"
#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/Logger.h"
#include <QRegularExpression>
#include <QVariant>

Config::Config( QObject* parent )
    : QObject( parent ), m_macMode( 0 ), m_fixedMac( "" ), m_ipv6Privacy( true ) {}

void Config::setConfigurationMap( const QVariantMap& configurationMap )
{
    QString macModeStr = configurationMap.value( "defaultMacMode" ).toString();
    if ( macModeStr == "fixed" ) setMacMode( 1 );
    else if ( macModeStr == "disabled" ) setMacMode( 2 );
    else setMacMode( 0 );
    setIpv6Privacy( configurationMap.value( "defaultIpv6Privacy", true ).toBool() );
}

void Config::setMacMode( int mode )
{
    if ( m_macMode != mode ) {
        m_macMode = mode;
        emit macModeChanged( mode );
        checkValidity();
    }
}

void Config::setFixedMac( const QString& mac )
{
    if ( m_fixedMac != mac ) {
        m_fixedMac = mac;
        emit fixedMacChanged( mac );
        checkValidity();
    }
}

void Config::setIpv6Privacy( bool enabled )
{
    if ( m_ipv6Privacy != enabled ) {
        m_ipv6Privacy = enabled;
        emit ipv6PrivacyChanged( enabled );
    }
}

bool Config::validateMacAddress( const QString& mac ) const
{
    QRegularExpression regex( "^([0-9A-Fa-f]{2}:){5}[0-9A-Fa-f]{2}$" );
    return regex.match( mac ).hasMatch();
}

bool Config::isValid() const
{
    if ( m_macMode == 1 ) return validateMacAddress( m_fixedMac );
    return true;
}

void Config::checkValidity() { emit validityChanged(); }

QString Config::macModeToString() const
{
    switch ( m_macMode ) {
        case 0: return "random";
        case 1: return "fixed";
        case 2: return "disabled";
        default: return "random";
    }
}

void Config::finalizeGlobalStorage() const
{
    auto* gs = Calamares::JobQueue::instance()->globalStorage();
    QVariantMap netPrivacyConfig;
    netPrivacyConfig.insert( "macMode", macModeToString() );
    netPrivacyConfig.insert( "fixedMac", m_fixedMac );
    netPrivacyConfig.insert( "ipv6Privacy", m_ipv6Privacy );
    gs->insert( "netPrivacy", netPrivacyConfig );
    cDebug() << "Network Privacy config saved:" << netPrivacyConfig;
}
