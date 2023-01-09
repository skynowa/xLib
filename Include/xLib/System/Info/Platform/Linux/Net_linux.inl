/**
 * \file  Net.inl
 * \brief system information
 */


namespace xl::system::info
{

//-------------------------------------------------------------------------------------------------
/**
 * https://unix.stackexchange.com/questions/40560/how-to-know-if-a-network-interface-is-tap-tun-bridge-or-physical
 *
 * Poking around in /sys/class/net I found the following distinctions:
 *
 * - Physical devices have a /sys/class/net/eth0/device symlink
 * - Bridges have a /sys/class/net/br0/bridge directory
 * - TUN and TAP devices have a /sys/class/net/tap0/tun_flags file
 * - Bridges and loopback interfaces have 00:00:00:00:00:00 in /sys/class/net/lo/address
 */
bool_t
Net::_isVpnActive_impl() const
{
    std::ctstring_t filePath = xT("/sys/class/net/tun0/tun_flags");

    FileInfo fileInfo(filePath);
    xCHECK_RET(!fileInfo.isExists(), false);

    return true;
}
//-------------------------------------------------------------------------------------------------

} // namespace
