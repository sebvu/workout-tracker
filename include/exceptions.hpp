#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>
#include <string>

// invalid argument count class
class InvalidArgumentCount : public std::exception {
  private:
  std::string message;

  public:
  explicit InvalidArgumentCount(int argc);
  const char *what() const noexcept override;
};

// invalid argument usage
class InvalidArgumentUsage : public std::exception {
  private:
  std::string message;

  public:
  explicit InvalidArgumentUsage(const std::string &arg);
  const char *what() const noexcept override;
};

class InvalidConfigurationFile : public std::exception {
  private:
  std::string message;

  public:
  explicit InvalidConfigurationFile(const std::string lookup);
  const char *what() const noexcept override;
};

#endif
