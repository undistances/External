binary_name="roblox-check"
directory="/usr/local/bin"

echo "[ Astel External Uninstallation ]"

if [ -f "$directory/$binary_name" ]; then
    sudo rm "$directory/$binary_name"
    echo "[ Uninstalled Successfully ]"
else
    echo "[ $binary_name Not Found, Already Uninstalled? ]"
fi
