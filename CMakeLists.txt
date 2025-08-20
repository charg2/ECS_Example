# CMakeList.txt: ECSExample에 대한 CMake 프로젝트, 여기에 소스를 포함하고
# 프로젝트 특정 논리를 정의합니다.
#
cmake_minimum_required (VERSION 3.8)

# 지원되는 경우 MSVC 컴파일러에 대해 핫 다시 로드 사용하도록 설정합니다.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("ECSExample")

# C++ 23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# FetchContent 모듈을 포함합니다.
include(FetchContent)

# EnTT를 다운로드하고 빌드 시스템에 통합합니다.
# EnTT의 GitHub 저장소 URL과 특정 태그(버전)를 지정합니다.
FetchContent_Declare(
  entt
  GIT_REPOSITORY https://github.com/skypjack/entt.git
  GIT_TAG        v3.13.0 # 원하는 EnTT 버전을 여기에 지정하세요. (최신 stable 버전 확인)
  GIT_SHALLOW    ON      # 전체 히스토리가 아닌 가장 최근 커밋만 가져옵니다.
)

# FetchContent_MakeAvailable을 호출하여 'entt' 프로젝트의 소스를 가져오고
# 해당 프로젝트의 CMakeLists.txt를 처리하여 EnTT::EnTT 대상을 사용할 수 있게 합니다.
FetchContent_MakeAvailable(entt)

# `Source` 디렉터리 내의 모든 .cpp 파일을 찾습니다.
file(GLOB_RECURSE ECS_SOURCES
    "Source/*.cpp"
)

# `Source` 디렉터리 내의 모든 헤더 파일(.h, .hpp 등)을 찾습니다.
file(GLOB_RECURSE ECS_HEADERS
    "Source/*.h"
    "Source/*.hpp"
	"Source/*.ixx"
)


# 이 프로젝트의 실행 파일에 소스를 추가합니다.
add_executable (ECSExample "ECSExample.cpp" "ECSExample.h" ${ECS_SOURCES} ${ECS_HEADERS})

set_property(TARGET ECSExample
    PROPERTY TARGET_PRECOMPILE_HEADERS_CREATE_AS
    "ECSPch.h"
)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ECSExample PROPERTY CXX_STANDARD 23)
endif()

# EnTT 라이브러리를 실행 파일에 링크합니다.
# FetchContent_MakeAvailable이 EnTT::EnTT 대상을 정의했으므로 이를 사용할 수 있습니다.
target_link_libraries(ECSExample PRIVATE EnTT::EnTT)
