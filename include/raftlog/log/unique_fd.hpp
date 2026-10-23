#pragma once
#include <fcntl.h>
#include <unistd.h>
#include <utility>

namespace raftlog::log
{
    class UniqueFd
    {
    private:
        int fd_ = -1;

    public:
        UniqueFd(const char *p, int flags)
        {
            fd_ = open(p, flags, 0644);
        }
        UniqueFd(UniqueFd &&other) noexcept
        {
            std::swap(this->fd_, other.fd_);
        }
        UniqueFd(const UniqueFd &other) = delete;
        UniqueFd &operator=(const UniqueFd &other) = delete;
        UniqueFd &operator=(UniqueFd &&other) noexcept
        {
            std::swap(this->fd_, other.fd_);
            return *this;
        }
        ~UniqueFd()
        {
            if (fd_ != -1)
                close(fd_);
        }

        int get_fd() const
        {
            return fd_;
        }
    };
}