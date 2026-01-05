# Calamares Network Privacy Module

Network Privacy Options module for Calamares installer - MAC randomization and IPv6 privacy extensions.

## Quick Start

Copy modules to Calamares source:

```bash
git clone https://github.com/SlowBearDigger/calamares-netprivacy
cd calamares-netprivacy
cp -r src/modules/* /path/to/calamares/src/modules/
```

Add to `settings.conf`:

```yaml
sequence:
  - show:
    - netprivacyq
  - exec:
    - netprivacycfg
```

## Modules

**netprivacyq** - QML View Module
- MAC spoofing (Random/Fixed/Disabled)
- IPv6 privacy extensions toggle
- Real-time MAC validation

**netprivacycfg** - Python Job Module
- Generates NetworkManager configs
- Generates systemd-networkd configs

## Testing

```bash
mkdir build && cd build
cmake ..
make calamares_viewmodule_netprivacyq
./netprivacytest
```

All tests pass (5/5).

## License

GPL-3.0-or-later
