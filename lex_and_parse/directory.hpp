#include <sys/types.h>
#include <dirent.h>
#include <string>
#include <vector>
#include <string.h>

class Directory
{
    public:
        Directory(const std::string& path);
        virtual ~Directory();
        bool get_directory_entries(std::vector<std::string>& entries);
        bool get_file_entries(std::vector<std::string>& entries);

    private:
        void open();
        void close();

        std::string _path;
        DIR* _dir;
};

Directory::Directory(const std::string& path)
{
    _path = path;
    open();
}

void Directory::open()
{
    _dir = opendir(_path.c_str());
    if (!_dir) {
        std::cout << "Failed to open the directory: " << strerror(errno) << "\n";
    }
}

void Directory::close()
{
    closedir(_dir);
}

Directory::~Directory()
{
    close();
}

bool Directory::get_directory_entries(std::vector<std::string>& entries)
{
    dirent* dir_ent;
    while ((dir_ent = readdir(_dir)) != NULL)
    {
        if (dir_ent->d_type == DT_DIR) {
            entries.push_back(std::string(dir_ent->d_name));
        }
    }
    rewinddir(_dir);
    return true;
}

bool Directory::get_file_entries(std::vector<std::string>& entries)
{
    if (!_dir)
        return false;

    dirent* dir_ent;
    while ((dir_ent = readdir(_dir)) != NULL)
    {
        if (dir_ent->d_type == DT_REG) {
            entries.push_back(std::string(dir_ent->d_name));
        }
    }
    rewinddir(_dir);
    return true;
}
