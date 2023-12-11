#ifndef CGI_HANDLER_HPP_
#define CGI_HANDLER_HPP_

#include <unistd.h>
#include <stdexcept>

#include "HttpRequest.hpp"
#include "RouteRule.hpp"
#include "SessionBlock.hpp"

#define DEFAULT_CONTENT_TYPE "text/html"
#define PIPE_READ  0
#define PIPE_WRITE 1
#define CGI_HANDLER_BUF_SIZE 134217728

class CgiHandler {
  public:
    CgiHandler(const HttpRequest& req, const RouteRule& route_rule);
    CgiHandler(const HttpRequest& req, const RouteRule& route_rule,
               const std::string& server_name, const int& port, const int& client_fd) throw(std::runtime_error);
    CgiHandler(const CgiHandler& other);
    CgiHandler& operator=(const CgiHandler& other);

    int                       getCgiReqEntityIdx(void);
    const HttpRequest&        getRequest(void);
    const int&                getReadPipeFromCgi(void) const;
    const bool&               getIsReadPipeFromCgiClosed(void) const;
    const int&                getWritePipetoCgi(void) const;
    const bool&               getIsWritePipeToCgiClosed(void) const;
    const int&                getPid(void) const;

    void                      setCgiReqEntityIdx(int idx);
    void                      setPipe(void) throw(std::runtime_error);
    void                      setupCgiEnvp(const std::map<std::string, SessionBlock>::const_iterator& sbi, bool is_joined_session);
    void                      setIsReadPipeFromCgiClosed(bool is_closed);
    void                      setIsWritePipeToCgiClosed(bool is_closed);

    int                       execute(const std::map<std::string, SessionBlock>::const_iterator& sbi, bool is_joined_session) throw(std::runtime_error);

    const int&                getClientFd(void) const;
    const std::vector<char>&  getBuf(void) const;
    const RouteRule&          getRouteRule(void) const;

    void                      addBuf(const char* buf, size_t size);
    void                      closeReadPipe(void);
    void                      closeWritePipe(void);

  private:
    int                       _idx;

    int                       _pipe_to_cgi_fd[2];
    bool                      _is_write_pipe_to_cgi_closed;
    int                       _pipe_from_cgi_fd[2];
    bool                      _is_read_pipe_from_cgi_closed;

    const HttpRequest&        _req;
    const RouteRule&          _route_rule;

    std::string               _server_name;
    int                       _port;

    std::vector<char>         _buf;
    int                       _client_fd;
    int                       _pid;
};


#endif
