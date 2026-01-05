#!/usr/bin/env python3
# === This file is part of Calamares - <https://calamares.io> ===
# SPDX-FileCopyrightText: 2026 Bounty Contributors
# SPDX-License-Identifier: GPL-3.0-or-later

import libcalamares
import os

def run():
    root_mount_point = libcalamares.globalstorage.value("rootMountPoint")
    net_privacy = libcalamares.globalstorage.value("netPrivacy")
    if not net_privacy:
        libcalamares.utils.warning("No network privacy configuration found")
        return None
    
    mac_mode = net_privacy.get("macMode", "random")
    fixed_mac = net_privacy.get("fixedMac", "")
    ipv6_privacy = net_privacy.get("ipv6Privacy", True)
    nm_conf_dir = os.path.join(root_mount_point, "usr/lib/NetworkManager/conf.d")
    os.makedirs(nm_conf_dir, exist_ok=True)
    
    if mac_mode == "random":
        with open(os.path.join(nm_conf_dir, "80_randomize-mac.conf"), "w") as f:
            f.write("[connection]\nwifi.cloned-mac-address=stable\nethernet.cloned-mac-address=stable\n")
    elif mac_mode == "fixed":
        with open(os.path.join(nm_conf_dir, "80_randomize-mac.conf"), "w") as f:
            f.write(f"[connection]\nwifi.cloned-mac-address={fixed_mac}\nethernet.cloned-mac-address={fixed_mac}\n")
    
    if ipv6_privacy:
        with open(os.path.join(nm_conf_dir, "80_ipv6-privacy.conf"), "w") as f:
            f.write("[connection]\nipv6.ip6-privacy=2\n")
        networkd_conf_dir = os.path.join(root_mount_point, "usr/lib/systemd/networkd.conf.d")
        os.makedirs(networkd_conf_dir, exist_ok=True)
        with open(os.path.join(networkd_conf_dir, "80_ipv6-privacy-extensions.conf"), "w") as f:
            f.write("[Network]\nIPv6PrivacyExtensions=kernel\n")
    return None
