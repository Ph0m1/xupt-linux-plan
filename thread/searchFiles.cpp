#include "mythreads.hpp"
#include <filesystem>

struct SearchConfig {
  std::string root_path; // 要搜索的根目录
  std::string file_type; // 要搜索的文件类型，如 ".txt"、".cpp" 等
  int max_concurrency;   // 最大并发数
  int max_depth;         // 最大搜索深度
  bool skip_hidden;      // 是否跳过隐藏文件或目录
  std::vector<std::string> skip_paths; // 要跳过的目录或文件的路径
};
class searcher {
public:
  SearchConfig config;
  void configer() {
    std::cout << "请输入配置信息：" << std::endl;
    std::cout << "请输入根目录路径：" << std::endl;
    std::cin >> this->config.root_path;
    std::cout << "请输入文件类型：" << std::endl;
    std::cin >> this->config.file_type;
    std::cout << "请输入最大并发数：" << std::endl;
    std::cin >> this->config.max_concurrency;
    std::cout << "请输入最大搜索深度：" << std::endl;
    std::cin >> this->config.max_depth;
    std::cout << "是否跳过隐藏文件或目录？(y/n)" << std::endl;
    char c;
    std::cin >> c;
    if (c == 'y') {
      this->config.skip_hidden = true;
    } else {
      this->config.skip_hidden = false;
    }
    std::cout << "请输入要跳过的目录或文件的路径(输入q结束): " << std::endl;
    std::string path;
    while (std::cin >> path) {
      if (path == "q")
        break;
      this->config.skip_paths.push_back(path);
    }
    std::cout << "配置信息已保存。" << std::endl;
    return;
  }


  void search() {
    std::filesystem::path root(this->config.root_path);
    if (!std::filesystem::exists(root)) {
      std::cout << "根目录不存在！" << std::endl;
      return;
    }
    if (!std::filesystem::is_directory(root)) {
      std::cout << "根目录不是一个目录！" << std::endl;
      return;
    }

    // 添加根目录到任务队列
    this->dirs.push_back(root.string());

    // 创建线程池
    ThreadPool pool(this->config.max_concurrency);
    while (!this->dirs.empty()) {
      std::string dir = this->dirs.back();
      this->dirs.pop_back();
      pool.enqueue([this, dir]() {
        this->search_dir(dir);
      });
    }
    
    std::cout << "搜索完成，找到 " << this->files.size() << " 个文件。" << std::endl;
    for (const auto &file : this->files) {
      std::cout << file << std::endl;
    }
    return;
  }

  void search_dir(const std::filesystem::path &dir) {
    for (const auto &entry : std::filesystem::directory_iterator(dir)) {
      if (std::filesystem::is_directory(entry.path())) {
        // 跳过隐藏目录
        if (this->config.skip_hidden && entry.is_regular_file() &&
            entry.path().filename().string()[0] == '.')
          continue;

        if (this->config.max_depth > 0) {
          if (--this->config.max_depth == 0)
            break;
        }
        // 跳过忽略的目录
        if (std::find(this->config.skip_paths.begin(),
                      this->config.skip_paths.end(),
                      entry.path().string()) != this->config.skip_paths.end()) {
          continue;
        }
        if (entry.is_directory()) {
          search_dir(entry.path());
        } else {
          if (entry.is_regular_file() &&
              entry.path().extension() == this->config.file_type) {
            this->files.push_back(entry.path().string());
          }
        }
      }
    }
  }

private:
  std::vector<std::string> dirs;
  std::vector<std::string> files;
};
int main() {
  searcher s;
  s.configer();
  s.search();
  return 0;
}
