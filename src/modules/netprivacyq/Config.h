/* === This file is part of Calamares - <https://calamares.io> ===
 *   SPDX-FileCopyrightText: 2026 Bounty Contributors
 *   SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef NETPRIVACY_CONFIG_H
#define NETPRIVACY_CONFIG_H

#include <QObject>
#include <QString>

class Config : public QObject
{
    Q_OBJECT
    Q_PROPERTY( int macMode READ macMode WRITE setMacMode NOTIFY macModeChanged )
    Q_PROPERTY( QString fixedMac READ fixedMac WRITE setFixedMac NOTIFY fixedMacChanged )
    Q_PROPERTY( bool ipv6Privacy READ ipv6Privacy WRITE setIpv6Privacy NOTIFY ipv6PrivacyChanged )
    Q_PROPERTY( bool isValid READ isValid NOTIFY validityChanged )

public:
    Config( QObject* parent = nullptr );
    void setConfigurationMap( const QVariantMap& configurationMap );
    int macMode() const { return m_macMode; }
    QString fixedMac() const { return m_fixedMac; }
    bool ipv6Privacy() const { return m_ipv6Privacy; }
    bool isValid() const;
    void setMacMode( int mode );
    void setFixedMac( const QString& mac );
    void setIpv6Privacy( bool enabled );
    Q_INVOKABLE bool validateMacAddress( const QString& mac ) const;
    Q_INVOKABLE void finalizeGlobalStorage() const;

signals:
    void macModeChanged( int mode );
    void fixedMacChanged( const QString& mac );
    void ipv6PrivacyChanged( bool enabled );
    void validityChanged();

private:
    int m_macMode;
    QString m_fixedMac;
    bool m_ipv6Privacy;
    void checkValidity();
    QString macModeToString() const;
};

#endif
