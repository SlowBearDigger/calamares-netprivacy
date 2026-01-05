/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2026 Bounty Contributors
 *   SPDX-License-Identifier: GPL-3.0-or-later
 */

import io.calamares.core 1.0
import io.calamares.ui 1.0

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

Page {
    id: netPrivacy
    
    // Explicit sizing to ensure visibility if parent binding fails
    width: parent ? parent.width : 800
    height: parent ? parent.height : 500

    header: Label {
        text: qsTr("Network Privacy Options")
        font.pointSize: 18
        font.bold: true
        padding: 20
        horizontalAlignment: Text.AlignHCenter
    }

    ScrollView {
        id: scrollView
        anchors.fill: parent
        anchors.topMargin: 20
        anchors.bottomMargin: 20
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        clip: true
        
        // This ensures the ScrollView knows the size of its content
        contentWidth: mainColumn.width
        contentHeight: mainColumn.height

        ColumnLayout {
            id: mainColumn
            width: scrollView.availableWidth
            spacing: 20

            // MAC Address Spoofing Section
            GroupBox {
                Layout.fillWidth: true
                title: qsTr("MAC Address Spoofing")

                ColumnLayout {
                    anchors.fill: parent
                    spacing: 10

                    RadioButton {
                        id: macRandom
                        text: qsTr("Random (NetworkManager stable cloning)")
                        checked: config.macMode === 0
                        onClicked: config.macMode = 0
                    }

                    RadioButton {
                        id: macFixed
                        text: qsTr("Fixed MAC address:")
                        checked: config.macMode === 1
                        onClicked: config.macMode = 1
                    }

                    RowLayout {
                        Layout.leftMargin: 30
                        enabled: macFixed.checked

                        TextField {
                            id: macInput
                            Layout.preferredWidth: 200
                            placeholderText: "00:11:22:33:44:55"
                            text: config.fixedMac
                            onTextChanged: config.fixedMac = text

                            validator: RegExpValidator {
                                regExp: /^([0-9A-Fa-f]{2}:){5}[0-9A-Fa-f]{2}$/
                            }
                        }

                        Text {
                            text: config.validateMacAddress(macInput.text) ? "✓" : "✗"
                            color: config.validateMacAddress(macInput.text) ? "green" : "red"
                            font.pointSize: 14
                            visible: macFixed.checked && macInput.text.length > 0
                        }
                    }

                    RadioButton {
                        id: macDisabled
                        text: qsTr("Disabled (use hardware MAC)")
                        checked: config.macMode === 2
                        onClicked: config.macMode = 2
                    }
                }
            }

            // IPv6 Privacy Section
            GroupBox {
                Layout.fillWidth: true
                title: qsTr("IPv6 Privacy")

                CheckBox {
                    id: ipv6Check
                    text: qsTr("Enable IPv6 Privacy Extensions")
                    checked: config.ipv6Privacy
                    onCheckedChanged: config.ipv6Privacy = checked
                }
            }

            // Info Text - Adding bottom padding/margin
            Label {
                Layout.fillWidth: true
                Layout.bottomMargin: 40
                text: qsTr("These settings will be applied during installation and can be changed later.")
                wrapMode: Text.WordWrap
                color: "#666"
                font.pointSize: 9
            }
        }
    }

    function onActivate() {
        // Called when page is shown
    }

    function onLeave() {
        // Save config to global storage
        // Now calling invokable method
        config.finalizeGlobalStorage()
    }
}
