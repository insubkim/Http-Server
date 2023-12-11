#include "RouteRule.hpp"
#include "HttpDecoderEnums.h"

RouteRule::RouteRule()
    : _accepted_methods(0 | 1 << (HPS::kGET) | 1 << (HPS::kPOST | 1 << (HPS::kDELETE))),
      _redirection(std::make_pair(0, "")),
      _autoIndex(false),
      _is_client_body_size_set(false),
      _max_client_body_size(0),
      _isCgi(false),
      _cgiPath("") {}

RouteRule::RouteRule(const RouteRule& other)
   : _route(other._route),
     _location(other._location),
     _accepted_methods(other._accepted_methods),
     _redirection(other._redirection),
     _autoIndex(other._autoIndex),
     _index_page(other._index_page),
     _error_pages(other._error_pages),
     _is_client_body_size_set(other._is_client_body_size_set),
     _max_client_body_size(other._max_client_body_size),
     _isCgi(other._isCgi),
     _cgiPath(other._cgiPath) {}

RouteRule& RouteRule::operator=(const RouteRule& other) {
  if (this == &other)
    return *this;
  _route = other._route;
  _location = other._location;
  _accepted_methods = other._accepted_methods;
  _redirection = other._redirection;
  _autoIndex = other._autoIndex;
  _index_page = other._index_page;
  _error_pages = other._error_pages;
  _is_client_body_size_set = other._is_client_body_size_set;
  _max_client_body_size = other._max_client_body_size;
  _isCgi = other._isCgi;
  _cgiPath = other._cgiPath;
  return *this;
}



const std::string&                  RouteRule::getRoute() const { return _route; }
const std::string&                  RouteRule::getLocation() const { return _location; }
int                                 RouteRule::getAcceptedMethods() const { return _accepted_methods; }
bool                                RouteRule::getIsClientBodySizeSet() const { return _is_client_body_size_set; }  
size_t                              RouteRule::getMaxClientBodySize() const { return _max_client_body_size; }
const std::pair<int, std::string>&  RouteRule::getRedirection() const { return _redirection; }
bool                                RouteRule::getAutoIndex() const { return _autoIndex; }
const std::string&                  RouteRule::getIndexPage() const { return _index_page; }
const std::string&                  RouteRule::getErrorPage(int code) const { return _error_pages.at(code); }
bool                                RouteRule::getIsCgi() const { return _isCgi; }
const std::string&                  RouteRule::getCgiPath() const { return _cgiPath; }

const std::string                   RouteRule::getRoot() const { return _location.empty() ? DEFAULT_ROOT : _location; }


void                                RouteRule::setRoute(const std::string& route) { _route = route; }
void                                RouteRule::setLocation(const std::string& location) { _location = location; }
void                                RouteRule::setAcceptedMethods(int methods) { _accepted_methods = methods; }
void                                RouteRule::setIsClientBodySizeSet(bool isSet) { _is_client_body_size_set = isSet; }
void                                RouteRule::setMaxClientBodySize(size_t maxSize) { _max_client_body_size = maxSize; }
void                                RouteRule::setRedirection(const std::pair<int, std::string>& redirection) { _redirection = redirection; }
void                                RouteRule::setIndexPage(const std::string& index) { _index_page = index; }
void                                RouteRule::setAutoIndex(bool enable) { _autoIndex = enable; }
void                                RouteRule::setIsCgi(bool isCgi) { _isCgi = isCgi; }
void                                RouteRule::setCgiPath(const std::string& cgiPath) { _cgiPath = cgiPath; }

bool  RouteRule::hasRedirection(int code) const { return _redirection.first == code; }

void  RouteRule::addRedirection(int code, const std::string& url) { _redirection = std::make_pair(code, url); }

bool  RouteRule::hasErrorPage(int code) const { return _error_pages.find(code) != _error_pages.end();}

void  RouteRule::addErrorPage(int code, const std::string& url) { _error_pages[code] = url; }



