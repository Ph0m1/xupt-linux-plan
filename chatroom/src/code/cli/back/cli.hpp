#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <vector>

#include "cli_command.hpp"

namespace cli {

class Back : public Command {
public:
  Back(const std::string &name, const std::string &description);

  void execute(const std::vector<std::string> &args) override;

  void help(const std::vector<std::string> &args) override;

private:
  nlohmann::json get_back_info();
};
} // namespace cli