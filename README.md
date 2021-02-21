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

It is advised to use docker for running the Resource Manager as mentioned in below steps:

1. Create docker image by running build_docker_resource_manager.sh. This creates docker image from docker file: Dockerfile.resourceManager.
2. Start docker container using run_docker_resource_manager.sh. 
3. Compile and install Resource Manager using following steps:
   a.) git clone https://github.com/vivekmsit/resource-manager.git
   b.) cd resource-manager
   c.) mkdir build
   d.) cd build
   e.) cmake ..
   f.) make
4. Run resource manager using following command: ./src/resource-manager & (This will run resource manager in the background).
5. Run http Client using command:
   ./utils/http-client/http_client --allocate user1 (For allocating resource to user1)
   ./utils/http-client/http_client --deallocate 1 (For deallocating resource ID 1)
   ./utils/http-client/http_client --list user1 (For listing resource IDs for user1)
   ./utils/http-client/http_client --listAll dummy (For listing resource IDs for all the users)

## Scope for Improvement
* Separate Database can be used for storing resource IDs information. Preferred library: sqlite.




