#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <sys/sysctl.h>
#include <sys/proc_info.h>
#include <libproc.h>
 
std::vector<std::string> targets = {
    "Roblox",
    "RobloxPlayer",
    "RobloxPlayerHelper"
};
 
struct Found {
    std::string name;
    pid_t pid;
};
 
std::vector<Found> findRoblox() {
    std::vector<Found> results;
 
    int mib[3] = { CTL_KERN, KERN_PROC, KERN_PROC_ALL };
    size_t size = 0;
 
    sysctl(mib, 3, nullptr, &size, nullptr, 0);
 
    std::vector<kinfo_proc> procs(size / sizeof(kinfo_proc));
    sysctl(mib, 3, procs.data(), &size, nullptr, 0);
 
    for (auto& proc : procs) {
        std::string pname(proc.kp_proc.p_comm);
        for (auto& target : targets) {
            if (pname == target) {
                results.push_back({ pname, proc.kp_proc.p_pid });
            }
        }
    }
 
    return results;
}
 
int main() {
    std::cout << "\n[ Astel External ]\n" << std::endl;
 
    auto found = findRoblox();
 
    if (!found.empty()) {
        std::cout << "[ Roblox Found ]\n" << std::endl;
        for (auto& f : found) {
            std::cout << "  -> " << f.name << " (PID: " << f.pid << ")" << std::endl;
        }
    } else {
        std::cout << "[ Roblox Not Found, Try Reopening Roblox ]" << std::endl;
    }
 
    std::cout << std::endl;
    return 0;
}
