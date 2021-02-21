#include <iostream>

#include <curlpp/Easy.hpp>
#include <curlpp/Infos.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/cURLpp.hpp>

#include <fstream>
#include <sstream>
#include <utility>
#include <string>
#include <optional>

#include <boost/program_options.hpp>

using namespace boost::program_options;

bool resourceManagerRequest(const std::string &requestUrl,
                            const std::optional <std::pair<std::string, std::string>> requestArgument,
                            std::string &responseData) {
    std::cout << "resourceManagerRequest() requestUrl: " << requestUrl << std::endl;
    try {
        curlpp::Cleanup myCleanup;
        std::string argumentSuffix = (requestArgument.has_value()) ? ("?" + requestArgument.value().first + "=" +
                                                                           requestArgument.value().second) : "";
        curlpp::options::Url myUrl(requestUrl + argumentSuffix);
        curlpp::Easy request;
        std::stringstream headers;
        request.setOpt(myUrl);
        std::stringstream httpResponse;
        request.setOpt(curlpp::options::WriteStream(&httpResponse));
        std::cout << "resourceManagerRequest()  request initialized" << std::endl;
        request.perform();
        auto res = curlpp::infos::ResponseCode::get(request);
        if (res == 200) {
            std::cout << "request was successful for url: " << requestUrl << std::endl;
            responseData = httpResponse.str();
            return true;
        } else {
            std::cout << "request failed for url: " << requestUrl << std::endl;
            return false;
        }
        return true;
    } catch (curlpp::RuntimeError &e) {
        std::cout << "resourceManagerRequest() error: " << e.what() << std::endl;
        return false;
    } catch (curlpp::LogicError &e) {
        std::cout << "resourceManagerRequest() error: " << e.what() << std::endl;
        return false;
    }
}

int main(int argc, const char *argv[]) {
    variables_map vm;
    try {
        options_description desc{"Options"};
        desc.add_options()(
                "allocate,alc", value<std::string>(), "call allocate API")(
                "deallocate,dalc", value<unsigned long>(), "call deallocate API")(
                "list,lst", value<std::string>(), "list resource IDs of a given user")(
                "listAll,lall", value<std::string>(), "list all resource IDs of all users");

        store(parse_command_line(argc, argv, desc), vm);
        notify(vm);

        if (vm.count("help")) {
            std::cout << desc << std::endl;
            return 0;
        }

    } catch (const std::exception &ex) {
        std::cerr << ex.what() << '\n';
        return EXIT_FAILURE;
    }

    std::string baseUrl = "http://localhost:8080/";

    if (vm.count("allocate")) {
        std::string userName = vm["allocate"].as<std::string>();
        std::cout << "calling allocate API for user name: " << userName << std::endl;
        std::string requestUrl = baseUrl + "allocate";
        std::string response{};
        std::optional <std::pair<std::string, std::string>> requestArgument({"user", userName});
        if (resourceManagerRequest(requestUrl, requestArgument, response)) {
            std::cout << "allocate API was successful, resource ID is: " << response << std::endl;
        } else {
            std::cout << "allocate API failed" << std::endl;
        }
    }

    if (vm.count("deallocate")) {
        unsigned long resourceId = vm["deallocate"].as<unsigned long>();
        std::cout << "calling deallocate API for resource ID: " << resourceId << std::endl;
        std::string requestUrl = baseUrl + "deallocate";
        std::string response{};
        std::optional <std::pair<std::string, std::string>> requestArgument({"resourceId", std::to_string(resourceId)});
        if (resourceManagerRequest(requestUrl, requestArgument, response)) {
            std::cout << "deallocate API was successful, resource ID is: " << response << std::endl;
        } else {
            std::cout << "allocate API failed" << std::endl;
        }
    }

    if (vm.count("list")) {
        std::string userName = vm["list"].as<std::string>();
        std::cout << "calling list API for user name: " << userName << std::endl;
        std::string requestUrl = baseUrl + "list";
        std::string response{};
        std::optional <std::pair<std::string, std::string>> requestArgument({"user", userName});
        if (resourceManagerRequest(requestUrl, requestArgument, response)) {
            std::cout << "list API was successful, list is: " << response << std::endl;
        } else {
            std::cout << "list API failed" << std::endl;
        }
    }

    if (vm.count("listAll")) {
        std::cout << "calling listAll API" << std::endl;
        std::string requestUrl = baseUrl + "listAll";
        std::string response{};
        std::optional <std::pair<std::string, std::string>> requestArgument;
        if (resourceManagerRequest(requestUrl, requestArgument, response)) {
            std::cout << "listAll API was successful, list is: " << response << std::endl;
        } else {
            std::cout << "listAll API failed" << std::endl;
        }
    }

    return 0;
}
