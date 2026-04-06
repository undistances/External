repository="https://raw.githubusercontent.com/undistances/External/refs/heads/main/Astel.cpp"
binary_name="inject"
directory="/usr/local/bin"

echo "[ Astel External Installation ]"
if ! command -v g++ &>/dev/null; then
  echo "XCode Is Needed For Installation, Please Rerun The Installer After XCode Is Installed"
  xcode-select --install
  exit 1
fi

tmp_directory=$(mktemp -d)

echo "[ Downloading Process ]"
curl -fsSL "$repository" -o "$tmp_directory/Astel.cpp"

if [ $? -ne 0 ]; then
    echo "[ Download Failed, Check Your Internet Connection ]"
    exit 1
fi
 
echo "[ Compiling... ]"
g++ -std=c++17 -o "$tmp_directory/$binary_name" "$tmp_directory/Astel.cpp"
 
if [ $? -ne 0 ]; then
    echo "[ Compilation Failed ]"
    exit 1
fi
 
echo "[ Installing... ]"
sudo mv "$tmp_directory/$binary_name" "$directory/$binary_name"
sudo chmod +x "$directory/$binary_name"
 
rm -rf "$tmp_directory"
 
echo "[ Installation Success, Run Application With: $binary_name ]"
