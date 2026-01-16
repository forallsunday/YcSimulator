# YcSimulator AI Coding Guidelines

## Project Overview
YcSimulator is a C++14 cross-platform simulation system for airborne camera and control systems. It consists of two main components:
- **YcControl** (executable): Airborne main control simulator that relays UDP messages between ICP (ground station software) and the camera simulation model.
- **libycSim.so** (shared library): Camera simulation model that interfaces with shared memory (via midware) and communicates with YcControl via UDP.

The system uses CMake for builds, supports multiple platforms (Windows, Linux x64, Linux ARM64), and employs multi-threading with thread-safe queues for message handling.

## Architecture
- **ControlSimulator** (`yc_control_sim/`): Manages UDP connections to ICP and camera simulator, routes messages based on FUNCTION_NODE_TYPE mappings.
- **CameraSimulator** (`yc_camera_sim/`): Multi-threaded camera simulation with 5 threads handling UDP reception, message queues (act_req/others), periodic updates (5ms), and subsystem timers.
- **Shared Memory Interface**: Uses `topic_read`/`topic_write` for I/O with midware, defined in `ModuleConfig.xml`.
- **UDP Communication**: Custom `UdpConnect` class with callback-based reception, used for ICP ↔ ControlSimulator ↔ CameraSimulator data flow.

## Build System
- Use CMake presets for configuration:
  - `linux-aarch64-win-cross-multiconfig`: Cross-compile ARM64 library from Windows
  - `windows-msvc`: MSVC build for Windows
  - `mingw-gcc75`: MinGW build
  - `linux-x64-multiconfig`: Native Linux x64
- Build commands: `cmake --preset <preset> && cmake --build build/<dir> --config <Release|Debug|RelWithDebInfo>`
- Only ARM64 builds produce `libycSim.so`; other platforms build `YcControl` and `TestUdpSend` executables.
- Outputs to `bin/${TARGET_PLATFORM}/$<CONFIG>/`

## Key Patterns & Conventions
- **Class Lifecycle**: Implement `init()`, `step()`, `freeze()`, `close()` methods for simulators.
- **UDP Usage**: Instantiate `UdpConnect(ip, recv_port, send_port, callback_func)` for connections.
- **Message Handling**: Use `thread_safe_queue<T>` for inter-thread communication.
- **Shared Memory**: Call `topic_read("TopicName", &struct, 0)` and `topic_write("TopicName", &struct, 0)`.
- **Configuration**: Parse IPs/ports from XML files using `tcp_udp_parse_d()` and `readUdpAddr()`.
- **Threading**: Use `std::thread` with lambdas for background tasks; manage with `std::atomic` flags.
- **Enums**: Use ICD-defined enums like `FUNCTION_NODE_TYPE` for node identification.
- **Logging**: Initialize with `log_init("filename.log")`; use `log_info()` for debug output.

## Critical Files
- `yc_camera_sim/model.cpp`: Implements midware interface (`usrmode_init`, `step_calculate`, etc.)
- `yc_control_sim/src/control_sim.cpp`: ControlSimulator implementation
- `yc_camera_sim/include/camera_sim.h`: CameraSimulator class definition
- `deps/include/udpconnect.h`: UDP communication wrapper
- `CMakeLists.txt`: Build configuration with platform-specific logic
- `ModuleConfig.xml` / `UDPNodeConfig_A.xml`: Runtime configuration files

## Development Workflow
- Modify simulator logic in respective `step()` methods.
- Add new message types by extending structs in `shm_interface.h` and updating XML configs.
- Test UDP communication using `TestUdpSend` executable.
- For ARM64 deployment: Build with cross-compile preset, deploy `libycSim.so` to docker1 with midware.
- Debug with logs; use `gdbserver.txt` for remote debugging notes.

## Common Pitfalls
- Ensure UDP ports are correctly mapped in XML configs; mismatches cause communication failures.
- Shared memory topics must match exactly between `topic_read`/`topic_write` calls.
- ARM64 builds exclude YcControl; use appropriate presets.
- Thread synchronization: Use atomic variables for flags; queues handle thread safety internally.</content>
<parameter name="filePath">d:\Documents\C-Project\YcSimulator\.github\copilot-instructions.md