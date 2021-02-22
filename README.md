### Resource Manager

## Description

Resource Manager is used for allocation/deallocation of resources to various users keeping track of available resources and allowing/rejecting allocation requests based on the availability of resources.

Resource Manager provides below mentioned APIs:

1. allocate = allocates resource for a given user -> returns resource ID
2. deallocate = deallocates resource ID -> returns error if invalid resource ID otherwise SUCCESS
3. list = returns list of resource IDs allocated for a given user
4. listAll = returns list of resource IDs allocated for all the users


## Implementation

Resource Manager has been implemented as HTTP server using libhttpserver library and should be run as part of docker container.
HTTP URL http://localhost:8080 is used as base URL for all the APIs.
Information about all the resources allocated currently is stored in RAM (as of now).

For Testing purpose, HTTP client has been implemented using CURL library.

## Usage

It is advised to use docker for running the Resource Manager. 
Use below mentioned steps to run resource manager:

1. Clone this repository. (git clone https://github.com/vivekmsit/resource-manager.git && cd resource-manager)
2. Create docker image by running build_docker_resource_manager.sh. This creates docker image from docker file: Dockerfile.resourceManager.
3. Start docker container using run_docker_resource_manager.sh. 
4. Compile and install Resource Manager using following steps:
   a.) mkdir build
   b.) cd build
   c.) cmake ..
   d.) make -j8 install
5. Run resource manager using following command: resource-manager & (This will run resource manager in the background). Resource manager
   will start HTTP server using URL http://localhost:8080.
6. Run http Client using command:
   http_client --allocate user1 (For allocating resource to user1)
   http_client --deallocate 1 (For deallocating resource ID 1)
   http_client --list user1 (For listing resource IDs for user1)
   http_client --listAll dummy (For listing resource IDs for all the users)

## Unit Tests

Unit tests can be compiled using BUILD_UNIT_TESTS=ON cmake argument: cmake -DBUILD_UNIT_TESTS=ON ..
Run unit tests using runAllTests command.

## Scope for Improvement
* Separate Database can be used for storing resource IDs information. Preferred library: sqlite.




