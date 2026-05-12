// Copyright 2020-2026 Ternaris
// SPDX-License-Identifier: Apache-2.0
// Generated from src/rosbags/typesys/stores/*.py; do not edit by hand.

struct GeneratedTypeDefinition {
  const char* msgtype;
  const char* msgdef;
};

const GeneratedTypeDefinition kEmptyTypes[] = {
    {R"RB(builtin_interfaces/msg/Duration)RB", R"RB(int32 sec
uint32 nanosec
)RB"},
    {R"RB(builtin_interfaces/msg/Time)RB", R"RB(int32 sec
uint32 nanosec
)RB"},
};

const GeneratedTypeDefinition kLatestTypes[] = {
    {R"RB(action_msgs/msg/GoalInfo)RB", R"RB(unique_identifier_msgs/msg/UUID goal_id
builtin_interfaces/msg/Time stamp
)RB"},
    {R"RB(action_msgs/msg/GoalStatus)RB", R"RB(int8 STATUS_UNKNOWN=0
int8 STATUS_ACCEPTED=1
int8 STATUS_EXECUTING=2
int8 STATUS_CANCELING=3
int8 STATUS_SUCCEEDED=4
int8 STATUS_CANCELED=5
int8 STATUS_ABORTED=6
action_msgs/msg/GoalInfo goal_info
int8 status
)RB"},
    {R"RB(action_msgs/msg/GoalStatusArray)RB", R"RB(action_msgs/msg/GoalStatus[] status_list
)RB"},
    {R"RB(actionlib_msgs/msg/GoalID)RB", R"RB(builtin_interfaces/msg/Time stamp
string id
)RB"},
    {R"RB(actionlib_msgs/msg/GoalStatus)RB", R"RB(uint8 PENDING=0
uint8 ACTIVE=1
uint8 PREEMPTED=2
uint8 SUCCEEDED=3
uint8 ABORTED=4
uint8 REJECTED=5
uint8 PREEMPTING=6
uint8 RECALLING=7
uint8 RECALLED=8
uint8 LOST=9
actionlib_msgs/msg/GoalID goal_id
uint8 status
string text
)RB"},
    {R"RB(actionlib_msgs/msg/GoalStatusArray)RB", R"RB(std_msgs/msg/Header header
actionlib_msgs/msg/GoalStatus[] status_list
)RB"},
    {R"RB(builtin_interfaces/msg/Duration)RB", R"RB(int32 sec
uint32 nanosec
)RB"},
    {R"RB(builtin_interfaces/msg/Time)RB", R"RB(int32 sec
uint32 nanosec
)RB"},
    {R"RB(diagnostic_msgs/msg/DiagnosticArray)RB", R"RB(std_msgs/msg/Header header
diagnostic_msgs/msg/DiagnosticStatus[] status
)RB"},
    {R"RB(diagnostic_msgs/msg/DiagnosticStatus)RB", R"RB(byte OK=0
byte WARN=1
byte ERROR=2
byte STALE=3
byte level
string name
string message
string hardware_id
diagnostic_msgs/msg/KeyValue[] values
)RB"},
    {R"RB(diagnostic_msgs/msg/KeyValue)RB", R"RB(string key
string value
)RB"},
    {R"RB(geometry_msgs/msg/Accel)RB", R"RB(geometry_msgs/msg/Vector3 linear
geometry_msgs/msg/Vector3 angular
)RB"},
    {R"RB(geometry_msgs/msg/AccelStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Accel accel
)RB"},
    {R"RB(geometry_msgs/msg/AccelWithCovariance)RB", R"RB(geometry_msgs/msg/Accel accel
float64[36] covariance
)RB"},
    {R"RB(geometry_msgs/msg/AccelWithCovarianceStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/AccelWithCovariance accel
)RB"},
    {R"RB(geometry_msgs/msg/Inertia)RB", R"RB(float64 m
geometry_msgs/msg/Vector3 com
float64 ixx
float64 ixy
float64 ixz
float64 iyy
float64 iyz
float64 izz
)RB"},
    {R"RB(geometry_msgs/msg/InertiaStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Inertia inertia
)RB"},
    {R"RB(geometry_msgs/msg/Point)RB", R"RB(float64 x
float64 y
float64 z
)RB"},
    {R"RB(geometry_msgs/msg/Point32)RB", R"RB(float32 x
float32 y
float32 z
)RB"},
    {R"RB(geometry_msgs/msg/PointStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Point point
)RB"},
    {R"RB(geometry_msgs/msg/Polygon)RB", R"RB(geometry_msgs/msg/Point32[] points
)RB"},
    {R"RB(geometry_msgs/msg/PolygonInstance)RB", R"RB(geometry_msgs/msg/Polygon polygon
int64 id
)RB"},
    {R"RB(geometry_msgs/msg/PolygonInstanceStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/PolygonInstance polygon
)RB"},
    {R"RB(geometry_msgs/msg/PolygonStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Polygon polygon
)RB"},
    {R"RB(geometry_msgs/msg/Pose)RB", R"RB(geometry_msgs/msg/Point position
geometry_msgs/msg/Quaternion orientation
)RB"},
    {R"RB(geometry_msgs/msg/Pose2D)RB", R"RB(float64 x
float64 y
float64 theta
)RB"},
    {R"RB(geometry_msgs/msg/PoseArray)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Pose[] poses
)RB"},
    {R"RB(geometry_msgs/msg/PoseStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Pose pose
)RB"},
    {R"RB(geometry_msgs/msg/PoseWithCovariance)RB", R"RB(geometry_msgs/msg/Pose pose
float64[36] covariance
)RB"},
    {R"RB(geometry_msgs/msg/PoseWithCovarianceStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/PoseWithCovariance pose
)RB"},
    {R"RB(geometry_msgs/msg/Quaternion)RB", R"RB(float64 x
float64 y
float64 z
float64 w
)RB"},
    {R"RB(geometry_msgs/msg/QuaternionStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Quaternion quaternion
)RB"},
    {R"RB(geometry_msgs/msg/Transform)RB", R"RB(geometry_msgs/msg/Vector3 translation
geometry_msgs/msg/Quaternion rotation
)RB"},
    {R"RB(geometry_msgs/msg/TransformStamped)RB", R"RB(std_msgs/msg/Header header
string child_frame_id
geometry_msgs/msg/Transform transform
)RB"},
    {R"RB(geometry_msgs/msg/Twist)RB", R"RB(geometry_msgs/msg/Vector3 linear
geometry_msgs/msg/Vector3 angular
)RB"},
    {R"RB(geometry_msgs/msg/TwistStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Twist twist
)RB"},
    {R"RB(geometry_msgs/msg/TwistWithCovariance)RB", R"RB(geometry_msgs/msg/Twist twist
float64[36] covariance
)RB"},
    {R"RB(geometry_msgs/msg/TwistWithCovarianceStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/TwistWithCovariance twist
)RB"},
    {R"RB(geometry_msgs/msg/Vector3)RB", R"RB(float64 x
float64 y
float64 z
)RB"},
    {R"RB(geometry_msgs/msg/Vector3Stamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Vector3 vector
)RB"},
    {R"RB(geometry_msgs/msg/VelocityStamped)RB", R"RB(std_msgs/msg/Header header
string body_frame_id
string reference_frame_id
geometry_msgs/msg/Twist velocity
)RB"},
    {R"RB(geometry_msgs/msg/Wrench)RB", R"RB(geometry_msgs/msg/Vector3 force
geometry_msgs/msg/Vector3 torque
)RB"},
    {R"RB(geometry_msgs/msg/WrenchStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Wrench wrench
)RB"},
    {R"RB(lifecycle_msgs/msg/State)RB", R"RB(uint8 PRIMARY_STATE_UNKNOWN=0
uint8 PRIMARY_STATE_UNCONFIGURED=1
uint8 PRIMARY_STATE_INACTIVE=2
uint8 PRIMARY_STATE_ACTIVE=3
uint8 PRIMARY_STATE_FINALIZED=4
uint8 TRANSITION_STATE_CONFIGURING=10
uint8 TRANSITION_STATE_CLEANINGUP=11
uint8 TRANSITION_STATE_SHUTTINGDOWN=12
uint8 TRANSITION_STATE_ACTIVATING=13
uint8 TRANSITION_STATE_DEACTIVATING=14
uint8 TRANSITION_STATE_ERRORPROCESSING=15
uint8 id
string label
)RB"},
    {R"RB(lifecycle_msgs/msg/Transition)RB", R"RB(uint8 TRANSITION_CREATE=0
uint8 TRANSITION_CONFIGURE=1
uint8 TRANSITION_CLEANUP=2
uint8 TRANSITION_ACTIVATE=3
uint8 TRANSITION_DEACTIVATE=4
uint8 TRANSITION_UNCONFIGURED_SHUTDOWN=5
uint8 TRANSITION_INACTIVE_SHUTDOWN=6
uint8 TRANSITION_ACTIVE_SHUTDOWN=7
uint8 TRANSITION_DESTROY=8
uint8 TRANSITION_ON_CONFIGURE_SUCCESS=10
uint8 TRANSITION_ON_CONFIGURE_FAILURE=11
uint8 TRANSITION_ON_CONFIGURE_ERROR=12
uint8 TRANSITION_ON_CLEANUP_SUCCESS=20
uint8 TRANSITION_ON_CLEANUP_FAILURE=21
uint8 TRANSITION_ON_CLEANUP_ERROR=22
uint8 TRANSITION_ON_ACTIVATE_SUCCESS=30
uint8 TRANSITION_ON_ACTIVATE_FAILURE=31
uint8 TRANSITION_ON_ACTIVATE_ERROR=32
uint8 TRANSITION_ON_DEACTIVATE_SUCCESS=40
uint8 TRANSITION_ON_DEACTIVATE_FAILURE=41
uint8 TRANSITION_ON_DEACTIVATE_ERROR=42
uint8 TRANSITION_ON_SHUTDOWN_SUCCESS=50
uint8 TRANSITION_ON_SHUTDOWN_FAILURE=51
uint8 TRANSITION_ON_SHUTDOWN_ERROR=52
uint8 TRANSITION_ON_ERROR_SUCCESS=60
uint8 TRANSITION_ON_ERROR_FAILURE=61
uint8 TRANSITION_ON_ERROR_ERROR=62
uint8 TRANSITION_CALLBACK_SUCCESS=97
uint8 TRANSITION_CALLBACK_FAILURE=98
uint8 TRANSITION_CALLBACK_ERROR=99
uint8 id
string label
)RB"},
    {R"RB(lifecycle_msgs/msg/TransitionDescription)RB", R"RB(lifecycle_msgs/msg/Transition transition
lifecycle_msgs/msg/State start_state
lifecycle_msgs/msg/State goal_state
)RB"},
    {R"RB(lifecycle_msgs/msg/TransitionEvent)RB", R"RB(uint64 timestamp
lifecycle_msgs/msg/Transition transition
lifecycle_msgs/msg/State start_state
lifecycle_msgs/msg/State goal_state
)RB"},
    {R"RB(nav_msgs/msg/Goals)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/PoseStamped[] goals
)RB"},
    {R"RB(nav_msgs/msg/GridCells)RB", R"RB(std_msgs/msg/Header header
float32 cell_width
float32 cell_height
geometry_msgs/msg/Point[] cells
)RB"},
    {R"RB(nav_msgs/msg/MapMetaData)RB", R"RB(builtin_interfaces/msg/Time map_load_time
float32 resolution
uint32 width
uint32 height
geometry_msgs/msg/Pose origin
)RB"},
    {R"RB(nav_msgs/msg/OccupancyGrid)RB", R"RB(std_msgs/msg/Header header
nav_msgs/msg/MapMetaData info
int8[] data
)RB"},
    {R"RB(nav_msgs/msg/Odometry)RB", R"RB(std_msgs/msg/Header header
string child_frame_id
geometry_msgs/msg/PoseWithCovariance pose
geometry_msgs/msg/TwistWithCovariance twist
)RB"},
    {R"RB(nav_msgs/msg/Path)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/PoseStamped[] poses
)RB"},
    {R"RB(rcl_interfaces/msg/FloatingPointRange)RB", R"RB(float64 from_value
float64 to_value
float64 step
)RB"},
    {R"RB(rcl_interfaces/msg/IntegerRange)RB", R"RB(int64 from_value
int64 to_value
uint64 step
)RB"},
    {R"RB(rcl_interfaces/msg/ListParametersResult)RB", R"RB(string[] names
string[] prefixes
)RB"},
    {R"RB(rcl_interfaces/msg/Log)RB", R"RB(uint8 DEBUG=10
uint8 INFO=20
uint8 WARN=30
uint8 ERROR=40
uint8 FATAL=50
builtin_interfaces/msg/Time stamp
uint8 level
string name
string msg
string file
string function
uint32 line
)RB"},
    {R"RB(rcl_interfaces/msg/LoggerLevel)RB", R"RB(uint8 LOG_LEVEL_UNKNOWN=0
uint8 LOG_LEVEL_DEBUG=10
uint8 LOG_LEVEL_INFO=20
uint8 LOG_LEVEL_WARN=30
uint8 LOG_LEVEL_ERROR=40
uint8 LOG_LEVEL_FATAL=50
string name
uint32 level
)RB"},
    {R"RB(rcl_interfaces/msg/Parameter)RB", R"RB(string name
rcl_interfaces/msg/ParameterValue value
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterDescriptor)RB", R"RB(string name
uint8 type
string description
string additional_constraints
bool read_only
bool dynamic_typing
rcl_interfaces/msg/FloatingPointRange[<=1] floating_point_range
rcl_interfaces/msg/IntegerRange[<=1] integer_range
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterEvent)RB", R"RB(builtin_interfaces/msg/Time stamp
string node
rcl_interfaces/msg/Parameter[] new_parameters
rcl_interfaces/msg/Parameter[] changed_parameters
rcl_interfaces/msg/Parameter[] deleted_parameters
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterEventDescriptors)RB", R"RB(rcl_interfaces/msg/ParameterDescriptor[] new_parameters
rcl_interfaces/msg/ParameterDescriptor[] changed_parameters
rcl_interfaces/msg/ParameterDescriptor[] deleted_parameters
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterType)RB", R"RB(uint8 PARAMETER_NOT_SET=0
uint8 PARAMETER_BOOL=1
uint8 PARAMETER_INTEGER=2
uint8 PARAMETER_DOUBLE=3
uint8 PARAMETER_STRING=4
uint8 PARAMETER_BYTE_ARRAY=5
uint8 PARAMETER_BOOL_ARRAY=6
uint8 PARAMETER_INTEGER_ARRAY=7
uint8 PARAMETER_DOUBLE_ARRAY=8
uint8 PARAMETER_STRING_ARRAY=9
uint8 structure_needs_at_least_one_member
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterValue)RB", R"RB(uint8 type
bool bool_value
int64 integer_value
float64 double_value
string string_value
byte[] byte_array_value
bool[] bool_array_value
int64[] integer_array_value
float64[] double_array_value
string[] string_array_value
)RB"},
    {R"RB(rcl_interfaces/msg/SetLoggerLevelsResult)RB", R"RB(bool successful
string reason
)RB"},
    {R"RB(rcl_interfaces/msg/SetParametersResult)RB", R"RB(bool successful
string reason
)RB"},
    {R"RB(rmw_dds_common/msg/Gid)RB", R"RB(char[16] data
)RB"},
    {R"RB(rmw_dds_common/msg/NodeEntitiesInfo)RB", R"RB(string<=256 node_namespace
string<=256 node_name
rmw_dds_common/msg/Gid[] reader_gid_seq
rmw_dds_common/msg/Gid[] writer_gid_seq
)RB"},
    {R"RB(rmw_dds_common/msg/ParticipantEntitiesInfo)RB", R"RB(rmw_dds_common/msg/Gid gid
rmw_dds_common/msg/NodeEntitiesInfo[] node_entities_info_seq
)RB"},
    {R"RB(rosbag2_interfaces/msg/ReadSplitEvent)RB", R"RB(string closed_file
string opened_file
string node_name
)RB"},
    {R"RB(rosbag2_interfaces/msg/WriteSplitEvent)RB", R"RB(string closed_file
string opened_file
string node_name
)RB"},
    {R"RB(rosgraph_msgs/msg/Clock)RB", R"RB(builtin_interfaces/msg/Time clock
)RB"},
    {R"RB(sensor_msgs/msg/BatteryState)RB", R"RB(uint8 POWER_SUPPLY_STATUS_UNKNOWN=0
uint8 POWER_SUPPLY_STATUS_CHARGING=1
uint8 POWER_SUPPLY_STATUS_DISCHARGING=2
uint8 POWER_SUPPLY_STATUS_NOT_CHARGING=3
uint8 POWER_SUPPLY_STATUS_FULL=4
uint8 POWER_SUPPLY_HEALTH_UNKNOWN=0
uint8 POWER_SUPPLY_HEALTH_GOOD=1
uint8 POWER_SUPPLY_HEALTH_OVERHEAT=2
uint8 POWER_SUPPLY_HEALTH_DEAD=3
uint8 POWER_SUPPLY_HEALTH_OVERVOLTAGE=4
uint8 POWER_SUPPLY_HEALTH_UNSPEC_FAILURE=5
uint8 POWER_SUPPLY_HEALTH_COLD=6
uint8 POWER_SUPPLY_HEALTH_WATCHDOG_TIMER_EXPIRE=7
uint8 POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE=8
uint8 POWER_SUPPLY_TECHNOLOGY_UNKNOWN=0
uint8 POWER_SUPPLY_TECHNOLOGY_NIMH=1
uint8 POWER_SUPPLY_TECHNOLOGY_LION=2
uint8 POWER_SUPPLY_TECHNOLOGY_LIPO=3
uint8 POWER_SUPPLY_TECHNOLOGY_LIFE=4
uint8 POWER_SUPPLY_TECHNOLOGY_NICD=5
uint8 POWER_SUPPLY_TECHNOLOGY_LIMN=6
uint8 POWER_SUPPLY_TECHNOLOGY_TERNARY=7
uint8 POWER_SUPPLY_TECHNOLOGY_VRLA=8
std_msgs/msg/Header header
float32 voltage
float32 temperature
float32 current
float32 charge
float32 capacity
float32 design_capacity
float32 percentage
uint8 power_supply_status
uint8 power_supply_health
uint8 power_supply_technology
bool present
float32[] cell_voltage
float32[] cell_temperature
string location
string serial_number
)RB"},
    {R"RB(sensor_msgs/msg/CameraInfo)RB", R"RB(std_msgs/msg/Header header
uint32 height
uint32 width
string distortion_model
float64[] d
float64[9] k
float64[9] r
float64[12] p
uint32 binning_x
uint32 binning_y
sensor_msgs/msg/RegionOfInterest roi
)RB"},
    {R"RB(sensor_msgs/msg/ChannelFloat32)RB", R"RB(string name
float32[] values
)RB"},
    {R"RB(sensor_msgs/msg/CompressedImage)RB", R"RB(std_msgs/msg/Header header
string format
uint8[] data
)RB"},
    {R"RB(sensor_msgs/msg/FluidPressure)RB", R"RB(std_msgs/msg/Header header
float64 fluid_pressure
float64 variance
)RB"},
    {R"RB(sensor_msgs/msg/Illuminance)RB", R"RB(std_msgs/msg/Header header
float64 illuminance
float64 variance
)RB"},
    {R"RB(sensor_msgs/msg/Image)RB", R"RB(std_msgs/msg/Header header
uint32 height
uint32 width
string encoding
uint8 is_bigendian
uint32 step
uint8[] data
)RB"},
    {R"RB(sensor_msgs/msg/Imu)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Quaternion orientation
float64[9] orientation_covariance
geometry_msgs/msg/Vector3 angular_velocity
float64[9] angular_velocity_covariance
geometry_msgs/msg/Vector3 linear_acceleration
float64[9] linear_acceleration_covariance
)RB"},
    {R"RB(sensor_msgs/msg/JointState)RB", R"RB(std_msgs/msg/Header header
string[] name
float64[] position
float64[] velocity
float64[] effort
)RB"},
    {R"RB(sensor_msgs/msg/Joy)RB", R"RB(std_msgs/msg/Header header
float32[] axes
int32[] buttons
)RB"},
    {R"RB(sensor_msgs/msg/JoyFeedback)RB", R"RB(uint8 TYPE_LED=0
uint8 TYPE_RUMBLE=1
uint8 TYPE_BUZZER=2
uint8 type
uint8 id
float32 intensity
)RB"},
    {R"RB(sensor_msgs/msg/JoyFeedbackArray)RB", R"RB(sensor_msgs/msg/JoyFeedback[] array
)RB"},
    {R"RB(sensor_msgs/msg/LaserEcho)RB", R"RB(float32[] echoes
)RB"},
    {R"RB(sensor_msgs/msg/LaserScan)RB", R"RB(std_msgs/msg/Header header
float32 angle_min
float32 angle_max
float32 angle_increment
float32 time_increment
float32 scan_time
float32 range_min
float32 range_max
float32[] ranges
float32[] intensities
)RB"},
    {R"RB(sensor_msgs/msg/MagneticField)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Vector3 magnetic_field
float64[9] magnetic_field_covariance
)RB"},
    {R"RB(sensor_msgs/msg/MultiDOFJointState)RB", R"RB(std_msgs/msg/Header header
string[] joint_names
geometry_msgs/msg/Transform[] transforms
geometry_msgs/msg/Twist[] twist
geometry_msgs/msg/Wrench[] wrench
)RB"},
    {R"RB(sensor_msgs/msg/MultiEchoLaserScan)RB", R"RB(std_msgs/msg/Header header
float32 angle_min
float32 angle_max
float32 angle_increment
float32 time_increment
float32 scan_time
float32 range_min
float32 range_max
sensor_msgs/msg/LaserEcho[] ranges
sensor_msgs/msg/LaserEcho[] intensities
)RB"},
    {R"RB(sensor_msgs/msg/NavSatFix)RB", R"RB(uint8 COVARIANCE_TYPE_UNKNOWN=0
uint8 COVARIANCE_TYPE_APPROXIMATED=1
uint8 COVARIANCE_TYPE_DIAGONAL_KNOWN=2
uint8 COVARIANCE_TYPE_KNOWN=3
std_msgs/msg/Header header
sensor_msgs/msg/NavSatStatus status
float64 latitude
float64 longitude
float64 altitude
float64[9] position_covariance
uint8 position_covariance_type
)RB"},
    {R"RB(sensor_msgs/msg/NavSatStatus)RB", R"RB(int8 STATUS_UNKNOWN=-2
int8 STATUS_NO_FIX=-1
int8 STATUS_FIX=0
int8 STATUS_SBAS_FIX=1
int8 STATUS_GBAS_FIX=2
uint16 SERVICE_UNKNOWN=0
uint16 SERVICE_GPS=1
uint16 SERVICE_GLONASS=2
uint16 SERVICE_COMPASS=4
uint16 SERVICE_GALILEO=8
int8 status
uint16 service
)RB"},
    {R"RB(sensor_msgs/msg/PointCloud)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Point32[] points
sensor_msgs/msg/ChannelFloat32[] channels
)RB"},
    {R"RB(sensor_msgs/msg/PointCloud2)RB", R"RB(std_msgs/msg/Header header
uint32 height
uint32 width
sensor_msgs/msg/PointField[] fields
bool is_bigendian
uint32 point_step
uint32 row_step
uint8[] data
bool is_dense
)RB"},
    {R"RB(sensor_msgs/msg/PointField)RB", R"RB(uint8 INT8=1
uint8 UINT8=2
uint8 INT16=3
uint8 UINT16=4
uint8 INT32=5
uint8 UINT32=6
uint8 FLOAT32=7
uint8 FLOAT64=8
string name
uint32 offset
uint8 datatype
uint32 count
)RB"},
    {R"RB(sensor_msgs/msg/Range)RB", R"RB(uint8 ULTRASOUND=0
uint8 INFRARED=1
std_msgs/msg/Header header
uint8 radiation_type
float32 field_of_view
float32 min_range
float32 max_range
float32 range
float32 variance
)RB"},
    {R"RB(sensor_msgs/msg/RegionOfInterest)RB", R"RB(uint32 x_offset
uint32 y_offset
uint32 height
uint32 width
bool do_rectify
)RB"},
    {R"RB(sensor_msgs/msg/RelativeHumidity)RB", R"RB(std_msgs/msg/Header header
float64 relative_humidity
float64 variance
)RB"},
    {R"RB(sensor_msgs/msg/Temperature)RB", R"RB(std_msgs/msg/Header header
float64 temperature
float64 variance
)RB"},
    {R"RB(sensor_msgs/msg/TimeReference)RB", R"RB(std_msgs/msg/Header header
builtin_interfaces/msg/Time time_ref
string source
)RB"},
    {R"RB(service_msgs/msg/ServiceEventInfo)RB", R"RB(uint8 REQUEST_SENT=0
uint8 REQUEST_RECEIVED=1
uint8 RESPONSE_SENT=2
uint8 RESPONSE_RECEIVED=3
uint8 event_type
builtin_interfaces/msg/Time stamp
char[16] client_gid
int64 sequence_number
)RB"},
    {R"RB(shape_msgs/msg/Mesh)RB", R"RB(shape_msgs/msg/MeshTriangle[] triangles
geometry_msgs/msg/Point[] vertices
)RB"},
    {R"RB(shape_msgs/msg/MeshTriangle)RB", R"RB(uint32[3] vertex_indices
)RB"},
    {R"RB(shape_msgs/msg/Plane)RB", R"RB(float64[4] coef
)RB"},
    {R"RB(shape_msgs/msg/SolidPrimitive)RB", R"RB(uint8 BOX=1
uint8 SPHERE=2
uint8 CYLINDER=3
uint8 CONE=4
uint8 PRISM=5
uint8 BOX_X=0
uint8 BOX_Y=1
uint8 BOX_Z=2
uint8 SPHERE_RADIUS=0
uint8 CYLINDER_HEIGHT=0
uint8 CYLINDER_RADIUS=1
uint8 CONE_HEIGHT=0
uint8 CONE_RADIUS=1
uint8 PRISM_HEIGHT=0
uint8 type
float64[<=3] dimensions
geometry_msgs/msg/Polygon polygon
)RB"},
    {R"RB(statistics_msgs/msg/MetricsMessage)RB", R"RB(string measurement_source_name
string metrics_source
string unit
builtin_interfaces/msg/Time window_start
builtin_interfaces/msg/Time window_stop
statistics_msgs/msg/StatisticDataPoint[] statistics
)RB"},
    {R"RB(statistics_msgs/msg/StatisticDataPoint)RB", R"RB(uint8 data_type
float64 data
)RB"},
    {R"RB(statistics_msgs/msg/StatisticDataType)RB", R"RB(uint8 STATISTICS_DATA_TYPE_UNINITIALIZED=0
uint8 STATISTICS_DATA_TYPE_AVERAGE=1
uint8 STATISTICS_DATA_TYPE_MINIMUM=2
uint8 STATISTICS_DATA_TYPE_MAXIMUM=3
uint8 STATISTICS_DATA_TYPE_STDDEV=4
uint8 STATISTICS_DATA_TYPE_SAMPLE_COUNT=5
uint8 structure_needs_at_least_one_member
)RB"},
    {R"RB(std_msgs/msg/Bool)RB", R"RB(bool data
)RB"},
    {R"RB(std_msgs/msg/Byte)RB", R"RB(byte data
)RB"},
    {R"RB(std_msgs/msg/ByteMultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
byte[] data
)RB"},
    {R"RB(std_msgs/msg/Char)RB", R"RB(char data
)RB"},
    {R"RB(std_msgs/msg/ColorRGBA)RB", R"RB(float32 r
float32 g
float32 b
float32 a
)RB"},
    {R"RB(std_msgs/msg/Empty)RB", R"RB(uint8 structure_needs_at_least_one_member
)RB"},
    {R"RB(std_msgs/msg/Float32)RB", R"RB(float32 data
)RB"},
    {R"RB(std_msgs/msg/Float32MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
float32[] data
)RB"},
    {R"RB(std_msgs/msg/Float64)RB", R"RB(float64 data
)RB"},
    {R"RB(std_msgs/msg/Float64MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
float64[] data
)RB"},
    {R"RB(std_msgs/msg/Header)RB", R"RB(builtin_interfaces/msg/Time stamp
string frame_id
)RB"},
    {R"RB(std_msgs/msg/Int16)RB", R"RB(int16 data
)RB"},
    {R"RB(std_msgs/msg/Int16MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
int16[] data
)RB"},
    {R"RB(std_msgs/msg/Int32)RB", R"RB(int32 data
)RB"},
    {R"RB(std_msgs/msg/Int32MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
int32[] data
)RB"},
    {R"RB(std_msgs/msg/Int64)RB", R"RB(int64 data
)RB"},
    {R"RB(std_msgs/msg/Int64MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
int64[] data
)RB"},
    {R"RB(std_msgs/msg/Int8)RB", R"RB(int8 data
)RB"},
    {R"RB(std_msgs/msg/Int8MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
int8[] data
)RB"},
    {R"RB(std_msgs/msg/MultiArrayDimension)RB", R"RB(string label
uint32 size
uint32 stride
)RB"},
    {R"RB(std_msgs/msg/MultiArrayLayout)RB", R"RB(std_msgs/msg/MultiArrayDimension[] dim
uint32 data_offset
)RB"},
    {R"RB(std_msgs/msg/String)RB", R"RB(string data
)RB"},
    {R"RB(std_msgs/msg/UInt16)RB", R"RB(uint16 data
)RB"},
    {R"RB(std_msgs/msg/UInt16MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
uint16[] data
)RB"},
    {R"RB(std_msgs/msg/UInt32)RB", R"RB(uint32 data
)RB"},
    {R"RB(std_msgs/msg/UInt32MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
uint32[] data
)RB"},
    {R"RB(std_msgs/msg/UInt64)RB", R"RB(uint64 data
)RB"},
    {R"RB(std_msgs/msg/UInt64MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
uint64[] data
)RB"},
    {R"RB(std_msgs/msg/UInt8)RB", R"RB(uint8 data
)RB"},
    {R"RB(std_msgs/msg/UInt8MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
uint8[] data
)RB"},
    {R"RB(stereo_msgs/msg/DisparityImage)RB", R"RB(std_msgs/msg/Header header
sensor_msgs/msg/Image image
float32 f
float32 t
sensor_msgs/msg/RegionOfInterest valid_window
float32 min_disparity
float32 max_disparity
float32 delta_d
)RB"},
    {R"RB(tf2_msgs/msg/TF2Error)RB", R"RB(uint8 NO_ERROR=0
uint8 LOOKUP_ERROR=1
uint8 CONNECTIVITY_ERROR=2
uint8 EXTRAPOLATION_ERROR=3
uint8 INVALID_ARGUMENT_ERROR=4
uint8 TIMEOUT_ERROR=5
uint8 TRANSFORM_ERROR=6
uint8 error
string error_string
)RB"},
    {R"RB(tf2_msgs/msg/TFMessage)RB", R"RB(geometry_msgs/msg/TransformStamped[] transforms
)RB"},
    {R"RB(trajectory_msgs/msg/JointTrajectory)RB", R"RB(std_msgs/msg/Header header
string[] joint_names
trajectory_msgs/msg/JointTrajectoryPoint[] points
)RB"},
    {R"RB(trajectory_msgs/msg/JointTrajectoryPoint)RB", R"RB(float64[] positions
float64[] velocities
float64[] accelerations
float64[] effort
builtin_interfaces/msg/Duration time_from_start
)RB"},
    {R"RB(trajectory_msgs/msg/MultiDOFJointTrajectory)RB", R"RB(std_msgs/msg/Header header
string[] joint_names
trajectory_msgs/msg/MultiDOFJointTrajectoryPoint[] points
)RB"},
    {R"RB(trajectory_msgs/msg/MultiDOFJointTrajectoryPoint)RB", R"RB(geometry_msgs/msg/Transform[] transforms
geometry_msgs/msg/Twist[] velocities
geometry_msgs/msg/Twist[] accelerations
builtin_interfaces/msg/Duration time_from_start
)RB"},
    {R"RB(type_description_interfaces/msg/Field)RB", R"RB(string name
type_description_interfaces/msg/FieldType type
string default_value
)RB"},
    {R"RB(type_description_interfaces/msg/FieldType)RB", R"RB(uint8 FIELD_TYPE_NOT_SET=0
uint8 FIELD_TYPE_NESTED_TYPE=1
uint8 FIELD_TYPE_INT8=2
uint8 FIELD_TYPE_UINT8=3
uint8 FIELD_TYPE_INT16=4
uint8 FIELD_TYPE_UINT16=5
uint8 FIELD_TYPE_INT32=6
uint8 FIELD_TYPE_UINT32=7
uint8 FIELD_TYPE_INT64=8
uint8 FIELD_TYPE_UINT64=9
uint8 FIELD_TYPE_FLOAT=10
uint8 FIELD_TYPE_DOUBLE=11
uint8 FIELD_TYPE_LONG_DOUBLE=12
uint8 FIELD_TYPE_CHAR=13
uint8 FIELD_TYPE_WCHAR=14
uint8 FIELD_TYPE_BOOLEAN=15
uint8 FIELD_TYPE_BYTE=16
uint8 FIELD_TYPE_STRING=17
uint8 FIELD_TYPE_WSTRING=18
uint8 FIELD_TYPE_FIXED_STRING=19
uint8 FIELD_TYPE_FIXED_WSTRING=20
uint8 FIELD_TYPE_BOUNDED_STRING=21
uint8 FIELD_TYPE_BOUNDED_WSTRING=22
uint8 FIELD_TYPE_NESTED_TYPE_ARRAY=49
uint8 FIELD_TYPE_INT8_ARRAY=50
uint8 FIELD_TYPE_UINT8_ARRAY=51
uint8 FIELD_TYPE_INT16_ARRAY=52
uint8 FIELD_TYPE_UINT16_ARRAY=53
uint8 FIELD_TYPE_INT32_ARRAY=54
uint8 FIELD_TYPE_UINT32_ARRAY=55
uint8 FIELD_TYPE_INT64_ARRAY=56
uint8 FIELD_TYPE_UINT64_ARRAY=57
uint8 FIELD_TYPE_FLOAT_ARRAY=58
uint8 FIELD_TYPE_DOUBLE_ARRAY=59
uint8 FIELD_TYPE_LONG_DOUBLE_ARRAY=60
uint8 FIELD_TYPE_CHAR_ARRAY=61
uint8 FIELD_TYPE_WCHAR_ARRAY=62
uint8 FIELD_TYPE_BOOLEAN_ARRAY=63
uint8 FIELD_TYPE_BYTE_ARRAY=64
uint8 FIELD_TYPE_STRING_ARRAY=65
uint8 FIELD_TYPE_WSTRING_ARRAY=66
uint8 FIELD_TYPE_FIXED_STRING_ARRAY=67
uint8 FIELD_TYPE_FIXED_WSTRING_ARRAY=68
uint8 FIELD_TYPE_BOUNDED_STRING_ARRAY=69
uint8 FIELD_TYPE_BOUNDED_WSTRING_ARRAY=70
uint8 FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE=97
uint8 FIELD_TYPE_INT8_BOUNDED_SEQUENCE=98
uint8 FIELD_TYPE_UINT8_BOUNDED_SEQUENCE=99
uint8 FIELD_TYPE_INT16_BOUNDED_SEQUENCE=100
uint8 FIELD_TYPE_UINT16_BOUNDED_SEQUENCE=101
uint8 FIELD_TYPE_INT32_BOUNDED_SEQUENCE=102
uint8 FIELD_TYPE_UINT32_BOUNDED_SEQUENCE=103
uint8 FIELD_TYPE_INT64_BOUNDED_SEQUENCE=104
uint8 FIELD_TYPE_UINT64_BOUNDED_SEQUENCE=105
uint8 FIELD_TYPE_FLOAT_BOUNDED_SEQUENCE=106
uint8 FIELD_TYPE_DOUBLE_BOUNDED_SEQUENCE=107
uint8 FIELD_TYPE_LONG_DOUBLE_BOUNDED_SEQUENCE=108
uint8 FIELD_TYPE_CHAR_BOUNDED_SEQUENCE=109
uint8 FIELD_TYPE_WCHAR_BOUNDED_SEQUENCE=110
uint8 FIELD_TYPE_BOOLEAN_BOUNDED_SEQUENCE=111
uint8 FIELD_TYPE_BYTE_BOUNDED_SEQUENCE=112
uint8 FIELD_TYPE_STRING_BOUNDED_SEQUENCE=113
uint8 FIELD_TYPE_WSTRING_BOUNDED_SEQUENCE=114
uint8 FIELD_TYPE_FIXED_STRING_BOUNDED_SEQUENCE=115
uint8 FIELD_TYPE_FIXED_WSTRING_BOUNDED_SEQUENCE=116
uint8 FIELD_TYPE_BOUNDED_STRING_BOUNDED_SEQUENCE=117
uint8 FIELD_TYPE_BOUNDED_WSTRING_BOUNDED_SEQUENCE=118
uint8 FIELD_TYPE_NESTED_TYPE_UNBOUNDED_SEQUENCE=145
uint8 FIELD_TYPE_INT8_UNBOUNDED_SEQUENCE=146
uint8 FIELD_TYPE_UINT8_UNBOUNDED_SEQUENCE=147
uint8 FIELD_TYPE_INT16_UNBOUNDED_SEQUENCE=148
uint8 FIELD_TYPE_UINT16_UNBOUNDED_SEQUENCE=149
uint8 FIELD_TYPE_INT32_UNBOUNDED_SEQUENCE=150
uint8 FIELD_TYPE_UINT32_UNBOUNDED_SEQUENCE=151
uint8 FIELD_TYPE_INT64_UNBOUNDED_SEQUENCE=152
uint8 FIELD_TYPE_UINT64_UNBOUNDED_SEQUENCE=153
uint8 FIELD_TYPE_FLOAT_UNBOUNDED_SEQUENCE=154
uint8 FIELD_TYPE_DOUBLE_UNBOUNDED_SEQUENCE=155
uint8 FIELD_TYPE_LONG_DOUBLE_UNBOUNDED_SEQUENCE=156
uint8 FIELD_TYPE_CHAR_UNBOUNDED_SEQUENCE=157
uint8 FIELD_TYPE_WCHAR_UNBOUNDED_SEQUENCE=158
uint8 FIELD_TYPE_BOOLEAN_UNBOUNDED_SEQUENCE=159
uint8 FIELD_TYPE_BYTE_UNBOUNDED_SEQUENCE=160
uint8 FIELD_TYPE_STRING_UNBOUNDED_SEQUENCE=161
uint8 FIELD_TYPE_WSTRING_UNBOUNDED_SEQUENCE=162
uint8 FIELD_TYPE_FIXED_STRING_UNBOUNDED_SEQUENCE=163
uint8 FIELD_TYPE_FIXED_WSTRING_UNBOUNDED_SEQUENCE=164
uint8 FIELD_TYPE_BOUNDED_STRING_UNBOUNDED_SEQUENCE=165
uint8 FIELD_TYPE_BOUNDED_WSTRING_UNBOUNDED_SEQUENCE=166
uint8 type_id
uint64 capacity
uint64 string_capacity
string<=255 nested_type_name
)RB"},
    {R"RB(type_description_interfaces/msg/IndividualTypeDescription)RB", R"RB(string<=255 type_name
type_description_interfaces/msg/Field[] fields
)RB"},
    {R"RB(type_description_interfaces/msg/KeyValue)RB", R"RB(string key
string value
)RB"},
    {R"RB(type_description_interfaces/msg/TypeDescription)RB", R"RB(type_description_interfaces/msg/IndividualTypeDescription type_description
type_description_interfaces/msg/IndividualTypeDescription[] referenced_type_descriptions
)RB"},
    {R"RB(type_description_interfaces/msg/TypeSource)RB", R"RB(string type_name
string encoding
string raw_file_contents
)RB"},
    {R"RB(unique_identifier_msgs/msg/UUID)RB", R"RB(uint8[16] uuid
)RB"},
    {R"RB(visualization_msgs/msg/ImageMarker)RB", R"RB(int32 CIRCLE=0
int32 LINE_STRIP=1
int32 LINE_LIST=2
int32 POLYGON=3
int32 POINTS=4
int32 ADD=0
int32 REMOVE=1
std_msgs/msg/Header header
string ns
int32 id
int32 type
int32 action
geometry_msgs/msg/Point position
float32 scale
std_msgs/msg/ColorRGBA outline_color
uint8 filled
std_msgs/msg/ColorRGBA fill_color
builtin_interfaces/msg/Duration lifetime
geometry_msgs/msg/Point[] points
std_msgs/msg/ColorRGBA[] outline_colors
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarker)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Pose pose
string name
string description
float32 scale
visualization_msgs/msg/MenuEntry[] menu_entries
visualization_msgs/msg/InteractiveMarkerControl[] controls
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerControl)RB", R"RB(uint8 INHERIT=0
uint8 FIXED=1
uint8 VIEW_FACING=2
uint8 NONE=0
uint8 MENU=1
uint8 BUTTON=2
uint8 MOVE_AXIS=3
uint8 MOVE_PLANE=4
uint8 ROTATE_AXIS=5
uint8 MOVE_ROTATE=6
uint8 MOVE_3D=7
uint8 ROTATE_3D=8
uint8 MOVE_ROTATE_3D=9
string name
geometry_msgs/msg/Quaternion orientation
uint8 orientation_mode
uint8 interaction_mode
bool always_visible
visualization_msgs/msg/Marker[] markers
bool independent_marker_orientation
string description
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerFeedback)RB", R"RB(uint8 KEEP_ALIVE=0
uint8 POSE_UPDATE=1
uint8 MENU_SELECT=2
uint8 BUTTON_CLICK=3
uint8 MOUSE_DOWN=4
uint8 MOUSE_UP=5
std_msgs/msg/Header header
string client_id
string marker_name
string control_name
uint8 event_type
geometry_msgs/msg/Pose pose
uint32 menu_entry_id
geometry_msgs/msg/Point mouse_point
bool mouse_point_valid
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerInit)RB", R"RB(string server_id
uint64 seq_num
visualization_msgs/msg/InteractiveMarker[] markers
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerPose)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Pose pose
string name
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerUpdate)RB", R"RB(uint8 KEEP_ALIVE=0
uint8 UPDATE=1
string server_id
uint64 seq_num
uint8 type
visualization_msgs/msg/InteractiveMarker[] markers
visualization_msgs/msg/InteractiveMarkerPose[] poses
string[] erases
)RB"},
    {R"RB(visualization_msgs/msg/Marker)RB", R"RB(int32 ARROW=0
int32 CUBE=1
int32 SPHERE=2
int32 CYLINDER=3
int32 LINE_STRIP=4
int32 LINE_LIST=5
int32 CUBE_LIST=6
int32 SPHERE_LIST=7
int32 POINTS=8
int32 TEXT_VIEW_FACING=9
int32 MESH_RESOURCE=10
int32 TRIANGLE_LIST=11
int32 ARROW_STRIP=12
int32 ADD=0
int32 MODIFY=0
int32 DELETE=2
int32 DELETEALL=3
std_msgs/msg/Header header
string ns
int32 id
int32 type
int32 action
geometry_msgs/msg/Pose pose
geometry_msgs/msg/Vector3 scale
std_msgs/msg/ColorRGBA color
builtin_interfaces/msg/Duration lifetime
bool frame_locked
geometry_msgs/msg/Point[] points
std_msgs/msg/ColorRGBA[] colors
string texture_resource
sensor_msgs/msg/CompressedImage texture
visualization_msgs/msg/UVCoordinate[] uv_coordinates
string text
string mesh_resource
visualization_msgs/msg/MeshFile mesh_file
bool mesh_use_embedded_materials
)RB"},
    {R"RB(visualization_msgs/msg/MarkerArray)RB", R"RB(visualization_msgs/msg/Marker[] markers
)RB"},
    {R"RB(visualization_msgs/msg/MenuEntry)RB", R"RB(uint8 FEEDBACK=0
uint8 ROSRUN=1
uint8 ROSLAUNCH=2
uint32 id
uint32 parent_id
string title
string command
uint8 command_type
)RB"},
    {R"RB(visualization_msgs/msg/MeshFile)RB", R"RB(string filename
uint8[] data
)RB"},
    {R"RB(visualization_msgs/msg/UVCoordinate)RB", R"RB(float32 u
float32 v
)RB"},
};

const GeneratedTypeDefinition kRos1NoeticTypes[] = {
    {R"RB(actionlib/msg/TestAction)RB", R"RB(actionlib/msg/TestActionGoal action_goal
actionlib/msg/TestActionResult action_result
actionlib/msg/TestActionFeedback action_feedback
)RB"},
    {R"RB(actionlib/msg/TestActionFeedback)RB", R"RB(std_msgs/msg/Header header
actionlib_msgs/msg/GoalStatus status
actionlib/msg/TestFeedback feedback
)RB"},
    {R"RB(actionlib/msg/TestActionGoal)RB", R"RB(std_msgs/msg/Header header
actionlib_msgs/msg/GoalID goal_id
actionlib/msg/TestGoal goal
)RB"},
    {R"RB(actionlib/msg/TestActionResult)RB", R"RB(std_msgs/msg/Header header
actionlib_msgs/msg/GoalStatus status
actionlib/msg/TestResult result
)RB"},
    {R"RB(actionlib/msg/TestFeedback)RB", R"RB(int32 feedback
)RB"},
    {R"RB(actionlib/msg/TestGoal)RB", R"RB(int32 goal
)RB"},
    {R"RB(actionlib/msg/TestRequestAction)RB", R"RB(actionlib/msg/TestRequestActionGoal action_goal
actionlib/msg/TestRequestActionResult action_result
actionlib/msg/TestRequestActionFeedback action_feedback
)RB"},
    {R"RB(actionlib/msg/TestRequestActionFeedback)RB", R"RB(std_msgs/msg/Header header
actionlib_msgs/msg/GoalStatus status
actionlib/msg/TestRequestFeedback feedback
)RB"},
    {R"RB(actionlib/msg/TestRequestActionGoal)RB", R"RB(std_msgs/msg/Header header
actionlib_msgs/msg/GoalID goal_id
actionlib/msg/TestRequestGoal goal
)RB"},
    {R"RB(actionlib/msg/TestRequestActionResult)RB", R"RB(std_msgs/msg/Header header
actionlib_msgs/msg/GoalStatus status
actionlib/msg/TestRequestResult result
)RB"},
    {R"RB(actionlib/msg/TestRequestFeedback)RB", R"RB(uint8 structure_needs_at_least_one_member
)RB"},
    {R"RB(actionlib/msg/TestRequestGoal)RB", R"RB(int32 TERMINATE_SUCCESS=0
int32 TERMINATE_ABORTED=1
int32 TERMINATE_REJECTED=2
int32 TERMINATE_LOSE=3
int32 TERMINATE_DROP=4
int32 TERMINATE_EXCEPTION=5
int32 terminate_status
bool ignore_cancel
string result_text
int32 the_result
bool is_simple_client
builtin_interfaces/msg/Duration delay_accept
builtin_interfaces/msg/Duration delay_terminate
builtin_interfaces/msg/Duration pause_status
)RB"},
    {R"RB(actionlib/msg/TestRequestResult)RB", R"RB(int32 the_result
bool is_simple_server
)RB"},
    {R"RB(actionlib/msg/TestResult)RB", R"RB(int32 result
)RB"},
    {R"RB(actionlib/msg/TwoIntsAction)RB", R"RB(actionlib/msg/TwoIntsActionGoal action_goal
actionlib/msg/TwoIntsActionResult action_result
actionlib/msg/TwoIntsActionFeedback action_feedback
)RB"},
    {R"RB(actionlib/msg/TwoIntsActionFeedback)RB", R"RB(std_msgs/msg/Header header
actionlib_msgs/msg/GoalStatus status
actionlib/msg/TwoIntsFeedback feedback
)RB"},
    {R"RB(actionlib/msg/TwoIntsActionGoal)RB", R"RB(std_msgs/msg/Header header
actionlib_msgs/msg/GoalID goal_id
actionlib/msg/TwoIntsGoal goal
)RB"},
    {R"RB(actionlib/msg/TwoIntsActionResult)RB", R"RB(std_msgs/msg/Header header
actionlib_msgs/msg/GoalStatus status
actionlib/msg/TwoIntsResult result
)RB"},
    {R"RB(actionlib/msg/TwoIntsFeedback)RB", R"RB(uint8 structure_needs_at_least_one_member
)RB"},
    {R"RB(actionlib/msg/TwoIntsGoal)RB", R"RB(int64 a
int64 b
)RB"},
    {R"RB(actionlib/msg/TwoIntsResult)RB", R"RB(int64 sum
)RB"},
    {R"RB(actionlib_msgs/msg/GoalID)RB", R"RB(builtin_interfaces/msg/Time stamp
string id
)RB"},
    {R"RB(actionlib_msgs/msg/GoalStatus)RB", R"RB(uint8 PENDING=0
uint8 ACTIVE=1
uint8 PREEMPTED=2
uint8 SUCCEEDED=3
uint8 ABORTED=4
uint8 REJECTED=5
uint8 PREEMPTING=6
uint8 RECALLING=7
uint8 RECALLED=8
uint8 LOST=9
actionlib_msgs/msg/GoalID goal_id
uint8 status
string text
)RB"},
    {R"RB(actionlib_msgs/msg/GoalStatusArray)RB", R"RB(std_msgs/msg/Header header
actionlib_msgs/msg/GoalStatus[] status_list
)RB"},
    {R"RB(bond/msg/Constants)RB", R"RB(float32 DEAD_PUBLISH_PERIOD=0.05
float32 DEFAULT_CONNECT_TIMEOUT=10.0
float32 DEFAULT_HEARTBEAT_TIMEOUT=4.0
float32 DEFAULT_DISCONNECT_TIMEOUT=2.0
float32 DEFAULT_HEARTBEAT_PERIOD=1.0
string DISABLE_HEARTBEAT_TIMEOUT_PARAM=/bond_disable_heartbeat_timeout
uint8 structure_needs_at_least_one_member
)RB"},
    {R"RB(bond/msg/Status)RB", R"RB(std_msgs/msg/Header header
string id
string instance_id
bool active
float32 heartbeat_timeout
float32 heartbeat_period
)RB"},
    {R"RB(builtin_interfaces/msg/Duration)RB", R"RB(int32 sec
uint32 nanosec
)RB"},
    {R"RB(builtin_interfaces/msg/Time)RB", R"RB(int32 sec
uint32 nanosec
)RB"},
    {R"RB(diagnostic_msgs/msg/DiagnosticArray)RB", R"RB(std_msgs/msg/Header header
diagnostic_msgs/msg/DiagnosticStatus[] status
)RB"},
    {R"RB(diagnostic_msgs/msg/DiagnosticStatus)RB", R"RB(byte OK=0
byte WARN=1
byte ERROR=2
byte STALE=3
byte level
string name
string message
string hardware_id
diagnostic_msgs/msg/KeyValue[] values
)RB"},
    {R"RB(diagnostic_msgs/msg/KeyValue)RB", R"RB(string key
string value
)RB"},
    {R"RB(dynamic_reconfigure/msg/BoolParameter)RB", R"RB(string name
bool value
)RB"},
    {R"RB(dynamic_reconfigure/msg/Config)RB", R"RB(dynamic_reconfigure/msg/BoolParameter[] bools
dynamic_reconfigure/msg/IntParameter[] ints
dynamic_reconfigure/msg/StrParameter[] strs
dynamic_reconfigure/msg/DoubleParameter[] doubles
dynamic_reconfigure/msg/GroupState[] groups
)RB"},
    {R"RB(dynamic_reconfigure/msg/ConfigDescription)RB", R"RB(dynamic_reconfigure/msg/Group[] groups
dynamic_reconfigure/msg/Config max
dynamic_reconfigure/msg/Config min
dynamic_reconfigure/msg/Config dflt
)RB"},
    {R"RB(dynamic_reconfigure/msg/DoubleParameter)RB", R"RB(string name
float64 value
)RB"},
    {R"RB(dynamic_reconfigure/msg/Group)RB", R"RB(string name
string type
dynamic_reconfigure/msg/ParamDescription[] parameters
int32 parent
int32 id
)RB"},
    {R"RB(dynamic_reconfigure/msg/GroupState)RB", R"RB(string name
bool state
int32 id
int32 parent
)RB"},
    {R"RB(dynamic_reconfigure/msg/IntParameter)RB", R"RB(string name
int32 value
)RB"},
    {R"RB(dynamic_reconfigure/msg/ParamDescription)RB", R"RB(string name
string type
uint32 level
string description
string edit_method
)RB"},
    {R"RB(dynamic_reconfigure/msg/SensorLevels)RB", R"RB(byte RECONFIGURE_CLOSE=3
byte RECONFIGURE_STOP=1
byte RECONFIGURE_RUNNING=0
uint8 structure_needs_at_least_one_member
)RB"},
    {R"RB(dynamic_reconfigure/msg/StrParameter)RB", R"RB(string name
string value
)RB"},
    {R"RB(geometry_msgs/msg/Accel)RB", R"RB(geometry_msgs/msg/Vector3 linear
geometry_msgs/msg/Vector3 angular
)RB"},
    {R"RB(geometry_msgs/msg/AccelStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Accel accel
)RB"},
    {R"RB(geometry_msgs/msg/AccelWithCovariance)RB", R"RB(geometry_msgs/msg/Accel accel
float64[36] covariance
)RB"},
    {R"RB(geometry_msgs/msg/AccelWithCovarianceStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/AccelWithCovariance accel
)RB"},
    {R"RB(geometry_msgs/msg/Inertia)RB", R"RB(float64 m
geometry_msgs/msg/Vector3 com
float64 ixx
float64 ixy
float64 ixz
float64 iyy
float64 iyz
float64 izz
)RB"},
    {R"RB(geometry_msgs/msg/InertiaStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Inertia inertia
)RB"},
    {R"RB(geometry_msgs/msg/Point)RB", R"RB(float64 x
float64 y
float64 z
)RB"},
    {R"RB(geometry_msgs/msg/Point32)RB", R"RB(float32 x
float32 y
float32 z
)RB"},
    {R"RB(geometry_msgs/msg/PointStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Point point
)RB"},
    {R"RB(geometry_msgs/msg/Polygon)RB", R"RB(geometry_msgs/msg/Point32[] points
)RB"},
    {R"RB(geometry_msgs/msg/PolygonStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Polygon polygon
)RB"},
    {R"RB(geometry_msgs/msg/Pose)RB", R"RB(geometry_msgs/msg/Point position
geometry_msgs/msg/Quaternion orientation
)RB"},
    {R"RB(geometry_msgs/msg/Pose2D)RB", R"RB(float64 x
float64 y
float64 theta
)RB"},
    {R"RB(geometry_msgs/msg/PoseArray)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Pose[] poses
)RB"},
    {R"RB(geometry_msgs/msg/PoseStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Pose pose
)RB"},
    {R"RB(geometry_msgs/msg/PoseWithCovariance)RB", R"RB(geometry_msgs/msg/Pose pose
float64[36] covariance
)RB"},
    {R"RB(geometry_msgs/msg/PoseWithCovarianceStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/PoseWithCovariance pose
)RB"},
    {R"RB(geometry_msgs/msg/Quaternion)RB", R"RB(float64 x
float64 y
float64 z
float64 w
)RB"},
    {R"RB(geometry_msgs/msg/QuaternionStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Quaternion quaternion
)RB"},
    {R"RB(geometry_msgs/msg/Transform)RB", R"RB(geometry_msgs/msg/Vector3 translation
geometry_msgs/msg/Quaternion rotation
)RB"},
    {R"RB(geometry_msgs/msg/TransformStamped)RB", R"RB(std_msgs/msg/Header header
string child_frame_id
geometry_msgs/msg/Transform transform
)RB"},
    {R"RB(geometry_msgs/msg/Twist)RB", R"RB(geometry_msgs/msg/Vector3 linear
geometry_msgs/msg/Vector3 angular
)RB"},
    {R"RB(geometry_msgs/msg/TwistStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Twist twist
)RB"},
    {R"RB(geometry_msgs/msg/TwistWithCovariance)RB", R"RB(geometry_msgs/msg/Twist twist
float64[36] covariance
)RB"},
    {R"RB(geometry_msgs/msg/TwistWithCovarianceStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/TwistWithCovariance twist
)RB"},
    {R"RB(geometry_msgs/msg/Vector3)RB", R"RB(float64 x
float64 y
float64 z
)RB"},
    {R"RB(geometry_msgs/msg/Vector3Stamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Vector3 vector
)RB"},
    {R"RB(geometry_msgs/msg/Wrench)RB", R"RB(geometry_msgs/msg/Vector3 force
geometry_msgs/msg/Vector3 torque
)RB"},
    {R"RB(geometry_msgs/msg/WrenchStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Wrench wrench
)RB"},
    {R"RB(nav_msgs/msg/GetMapAction)RB", R"RB(nav_msgs/msg/GetMapActionGoal action_goal
nav_msgs/msg/GetMapActionResult action_result
nav_msgs/msg/GetMapActionFeedback action_feedback
)RB"},
    {R"RB(nav_msgs/msg/GetMapActionFeedback)RB", R"RB(std_msgs/msg/Header header
actionlib_msgs/msg/GoalStatus status
nav_msgs/msg/GetMapFeedback feedback
)RB"},
    {R"RB(nav_msgs/msg/GetMapActionGoal)RB", R"RB(std_msgs/msg/Header header
actionlib_msgs/msg/GoalID goal_id
nav_msgs/msg/GetMapGoal goal
)RB"},
    {R"RB(nav_msgs/msg/GetMapActionResult)RB", R"RB(std_msgs/msg/Header header
actionlib_msgs/msg/GoalStatus status
nav_msgs/msg/GetMapResult result
)RB"},
    {R"RB(nav_msgs/msg/GetMapFeedback)RB", R"RB(uint8 structure_needs_at_least_one_member
)RB"},
    {R"RB(nav_msgs/msg/GetMapGoal)RB", R"RB(uint8 structure_needs_at_least_one_member
)RB"},
    {R"RB(nav_msgs/msg/GetMapResult)RB", R"RB(nav_msgs/msg/OccupancyGrid map
)RB"},
    {R"RB(nav_msgs/msg/GridCells)RB", R"RB(std_msgs/msg/Header header
float32 cell_width
float32 cell_height
geometry_msgs/msg/Point[] cells
)RB"},
    {R"RB(nav_msgs/msg/MapMetaData)RB", R"RB(builtin_interfaces/msg/Time map_load_time
float32 resolution
uint32 width
uint32 height
geometry_msgs/msg/Pose origin
)RB"},
    {R"RB(nav_msgs/msg/OccupancyGrid)RB", R"RB(std_msgs/msg/Header header
nav_msgs/msg/MapMetaData info
int8[] data
)RB"},
    {R"RB(nav_msgs/msg/Odometry)RB", R"RB(std_msgs/msg/Header header
string child_frame_id
geometry_msgs/msg/PoseWithCovariance pose
geometry_msgs/msg/TwistWithCovariance twist
)RB"},
    {R"RB(nav_msgs/msg/Path)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/PoseStamped[] poses
)RB"},
    {R"RB(roscpp/msg/Logger)RB", R"RB(string name
string level
)RB"},
    {R"RB(rosgraph_msgs/msg/Clock)RB", R"RB(builtin_interfaces/msg/Time clock
)RB"},
    {R"RB(rosgraph_msgs/msg/Log)RB", R"RB(byte DEBUG=1
byte INFO=2
byte WARN=4
byte ERROR=8
byte FATAL=16
std_msgs/msg/Header header
byte level
string name
string msg
string file
string function
uint32 line
string[] topics
)RB"},
    {R"RB(rosgraph_msgs/msg/TopicStatistics)RB", R"RB(string topic
string node_pub
string node_sub
builtin_interfaces/msg/Time window_start
builtin_interfaces/msg/Time window_stop
int32 delivered_msgs
int32 dropped_msgs
int32 traffic
builtin_interfaces/msg/Duration period_mean
builtin_interfaces/msg/Duration period_stddev
builtin_interfaces/msg/Duration period_max
builtin_interfaces/msg/Duration stamp_age_mean
builtin_interfaces/msg/Duration stamp_age_stddev
builtin_interfaces/msg/Duration stamp_age_max
)RB"},
    {R"RB(sensor_msgs/msg/BatteryState)RB", R"RB(uint8 POWER_SUPPLY_STATUS_UNKNOWN=0
uint8 POWER_SUPPLY_STATUS_CHARGING=1
uint8 POWER_SUPPLY_STATUS_DISCHARGING=2
uint8 POWER_SUPPLY_STATUS_NOT_CHARGING=3
uint8 POWER_SUPPLY_STATUS_FULL=4
uint8 POWER_SUPPLY_HEALTH_UNKNOWN=0
uint8 POWER_SUPPLY_HEALTH_GOOD=1
uint8 POWER_SUPPLY_HEALTH_OVERHEAT=2
uint8 POWER_SUPPLY_HEALTH_DEAD=3
uint8 POWER_SUPPLY_HEALTH_OVERVOLTAGE=4
uint8 POWER_SUPPLY_HEALTH_UNSPEC_FAILURE=5
uint8 POWER_SUPPLY_HEALTH_COLD=6
uint8 POWER_SUPPLY_HEALTH_WATCHDOG_TIMER_EXPIRE=7
uint8 POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE=8
uint8 POWER_SUPPLY_TECHNOLOGY_UNKNOWN=0
uint8 POWER_SUPPLY_TECHNOLOGY_NIMH=1
uint8 POWER_SUPPLY_TECHNOLOGY_LION=2
uint8 POWER_SUPPLY_TECHNOLOGY_LIPO=3
uint8 POWER_SUPPLY_TECHNOLOGY_LIFE=4
uint8 POWER_SUPPLY_TECHNOLOGY_NICD=5
uint8 POWER_SUPPLY_TECHNOLOGY_LIMN=6
std_msgs/msg/Header header
float32 voltage
float32 temperature
float32 current
float32 charge
float32 capacity
float32 design_capacity
float32 percentage
uint8 power_supply_status
uint8 power_supply_health
uint8 power_supply_technology
bool present
float32[] cell_voltage
float32[] cell_temperature
string location
string serial_number
)RB"},
    {R"RB(sensor_msgs/msg/CameraInfo)RB", R"RB(std_msgs/msg/Header header
uint32 height
uint32 width
string distortion_model
float64[] D
float64[9] K
float64[9] R
float64[12] P
uint32 binning_x
uint32 binning_y
sensor_msgs/msg/RegionOfInterest roi
)RB"},
    {R"RB(sensor_msgs/msg/ChannelFloat32)RB", R"RB(string name
float32[] values
)RB"},
    {R"RB(sensor_msgs/msg/CompressedImage)RB", R"RB(std_msgs/msg/Header header
string format
uint8[] data
)RB"},
    {R"RB(sensor_msgs/msg/FluidPressure)RB", R"RB(std_msgs/msg/Header header
float64 fluid_pressure
float64 variance
)RB"},
    {R"RB(sensor_msgs/msg/Illuminance)RB", R"RB(std_msgs/msg/Header header
float64 illuminance
float64 variance
)RB"},
    {R"RB(sensor_msgs/msg/Image)RB", R"RB(std_msgs/msg/Header header
uint32 height
uint32 width
string encoding
uint8 is_bigendian
uint32 step
uint8[] data
)RB"},
    {R"RB(sensor_msgs/msg/Imu)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Quaternion orientation
float64[9] orientation_covariance
geometry_msgs/msg/Vector3 angular_velocity
float64[9] angular_velocity_covariance
geometry_msgs/msg/Vector3 linear_acceleration
float64[9] linear_acceleration_covariance
)RB"},
    {R"RB(sensor_msgs/msg/JointState)RB", R"RB(std_msgs/msg/Header header
string[] name
float64[] position
float64[] velocity
float64[] effort
)RB"},
    {R"RB(sensor_msgs/msg/Joy)RB", R"RB(std_msgs/msg/Header header
float32[] axes
int32[] buttons
)RB"},
    {R"RB(sensor_msgs/msg/JoyFeedback)RB", R"RB(uint8 TYPE_LED=0
uint8 TYPE_RUMBLE=1
uint8 TYPE_BUZZER=2
uint8 type
uint8 id
float32 intensity
)RB"},
    {R"RB(sensor_msgs/msg/JoyFeedbackArray)RB", R"RB(sensor_msgs/msg/JoyFeedback[] array
)RB"},
    {R"RB(sensor_msgs/msg/LaserEcho)RB", R"RB(float32[] echoes
)RB"},
    {R"RB(sensor_msgs/msg/LaserScan)RB", R"RB(std_msgs/msg/Header header
float32 angle_min
float32 angle_max
float32 angle_increment
float32 time_increment
float32 scan_time
float32 range_min
float32 range_max
float32[] ranges
float32[] intensities
)RB"},
    {R"RB(sensor_msgs/msg/MagneticField)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Vector3 magnetic_field
float64[9] magnetic_field_covariance
)RB"},
    {R"RB(sensor_msgs/msg/MultiDOFJointState)RB", R"RB(std_msgs/msg/Header header
string[] joint_names
geometry_msgs/msg/Transform[] transforms
geometry_msgs/msg/Twist[] twist
geometry_msgs/msg/Wrench[] wrench
)RB"},
    {R"RB(sensor_msgs/msg/MultiEchoLaserScan)RB", R"RB(std_msgs/msg/Header header
float32 angle_min
float32 angle_max
float32 angle_increment
float32 time_increment
float32 scan_time
float32 range_min
float32 range_max
sensor_msgs/msg/LaserEcho[] ranges
sensor_msgs/msg/LaserEcho[] intensities
)RB"},
    {R"RB(sensor_msgs/msg/NavSatFix)RB", R"RB(uint8 COVARIANCE_TYPE_UNKNOWN=0
uint8 COVARIANCE_TYPE_APPROXIMATED=1
uint8 COVARIANCE_TYPE_DIAGONAL_KNOWN=2
uint8 COVARIANCE_TYPE_KNOWN=3
std_msgs/msg/Header header
sensor_msgs/msg/NavSatStatus status
float64 latitude
float64 longitude
float64 altitude
float64[9] position_covariance
uint8 position_covariance_type
)RB"},
    {R"RB(sensor_msgs/msg/NavSatStatus)RB", R"RB(int8 STATUS_NO_FIX=-1
int8 STATUS_FIX=0
int8 STATUS_SBAS_FIX=1
int8 STATUS_GBAS_FIX=2
uint16 SERVICE_GPS=1
uint16 SERVICE_GLONASS=2
uint16 SERVICE_COMPASS=4
uint16 SERVICE_GALILEO=8
int8 status
uint16 service
)RB"},
    {R"RB(sensor_msgs/msg/PointCloud)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Point32[] points
sensor_msgs/msg/ChannelFloat32[] channels
)RB"},
    {R"RB(sensor_msgs/msg/PointCloud2)RB", R"RB(std_msgs/msg/Header header
uint32 height
uint32 width
sensor_msgs/msg/PointField[] fields
bool is_bigendian
uint32 point_step
uint32 row_step
uint8[] data
bool is_dense
)RB"},
    {R"RB(sensor_msgs/msg/PointField)RB", R"RB(uint8 INT8=1
uint8 UINT8=2
uint8 INT16=3
uint8 UINT16=4
uint8 INT32=5
uint8 UINT32=6
uint8 FLOAT32=7
uint8 FLOAT64=8
string name
uint32 offset
uint8 datatype
uint32 count
)RB"},
    {R"RB(sensor_msgs/msg/Range)RB", R"RB(uint8 ULTRASOUND=0
uint8 INFRARED=1
std_msgs/msg/Header header
uint8 radiation_type
float32 field_of_view
float32 min_range
float32 max_range
float32 range
)RB"},
    {R"RB(sensor_msgs/msg/RegionOfInterest)RB", R"RB(uint32 x_offset
uint32 y_offset
uint32 height
uint32 width
bool do_rectify
)RB"},
    {R"RB(sensor_msgs/msg/RelativeHumidity)RB", R"RB(std_msgs/msg/Header header
float64 relative_humidity
float64 variance
)RB"},
    {R"RB(sensor_msgs/msg/Temperature)RB", R"RB(std_msgs/msg/Header header
float64 temperature
float64 variance
)RB"},
    {R"RB(sensor_msgs/msg/TimeReference)RB", R"RB(std_msgs/msg/Header header
builtin_interfaces/msg/Time time_ref
string source
)RB"},
    {R"RB(shape_msgs/msg/Mesh)RB", R"RB(shape_msgs/msg/MeshTriangle[] triangles
geometry_msgs/msg/Point[] vertices
)RB"},
    {R"RB(shape_msgs/msg/MeshTriangle)RB", R"RB(uint32[3] vertex_indices
)RB"},
    {R"RB(shape_msgs/msg/Plane)RB", R"RB(float64[4] coef
)RB"},
    {R"RB(shape_msgs/msg/SolidPrimitive)RB", R"RB(uint8 BOX=1
uint8 SPHERE=2
uint8 CYLINDER=3
uint8 CONE=4
uint8 BOX_X=0
uint8 BOX_Y=1
uint8 BOX_Z=2
uint8 SPHERE_RADIUS=0
uint8 CYLINDER_HEIGHT=0
uint8 CYLINDER_RADIUS=1
uint8 CONE_HEIGHT=0
uint8 CONE_RADIUS=1
uint8 type
float64[] dimensions
)RB"},
    {R"RB(std_msgs/msg/Bool)RB", R"RB(bool data
)RB"},
    {R"RB(std_msgs/msg/Byte)RB", R"RB(byte data
)RB"},
    {R"RB(std_msgs/msg/ByteMultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
byte[] data
)RB"},
    {R"RB(std_msgs/msg/Char)RB", R"RB(char data
)RB"},
    {R"RB(std_msgs/msg/ColorRGBA)RB", R"RB(float32 r
float32 g
float32 b
float32 a
)RB"},
    {R"RB(std_msgs/msg/Duration)RB", R"RB(builtin_interfaces/msg/Duration data
)RB"},
    {R"RB(std_msgs/msg/Empty)RB", R"RB(uint8 structure_needs_at_least_one_member
)RB"},
    {R"RB(std_msgs/msg/Float32)RB", R"RB(float32 data
)RB"},
    {R"RB(std_msgs/msg/Float32MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
float32[] data
)RB"},
    {R"RB(std_msgs/msg/Float64)RB", R"RB(float64 data
)RB"},
    {R"RB(std_msgs/msg/Float64MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
float64[] data
)RB"},
    {R"RB(std_msgs/msg/Header)RB", R"RB(uint32 seq
builtin_interfaces/msg/Time stamp
string frame_id
)RB"},
    {R"RB(std_msgs/msg/Int16)RB", R"RB(int16 data
)RB"},
    {R"RB(std_msgs/msg/Int16MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
int16[] data
)RB"},
    {R"RB(std_msgs/msg/Int32)RB", R"RB(int32 data
)RB"},
    {R"RB(std_msgs/msg/Int32MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
int32[] data
)RB"},
    {R"RB(std_msgs/msg/Int64)RB", R"RB(int64 data
)RB"},
    {R"RB(std_msgs/msg/Int64MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
int64[] data
)RB"},
    {R"RB(std_msgs/msg/Int8)RB", R"RB(int8 data
)RB"},
    {R"RB(std_msgs/msg/Int8MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
int8[] data
)RB"},
    {R"RB(std_msgs/msg/MultiArrayDimension)RB", R"RB(string label
uint32 size
uint32 stride
)RB"},
    {R"RB(std_msgs/msg/MultiArrayLayout)RB", R"RB(std_msgs/msg/MultiArrayDimension[] dim
uint32 data_offset
)RB"},
    {R"RB(std_msgs/msg/String)RB", R"RB(string data
)RB"},
    {R"RB(std_msgs/msg/Time)RB", R"RB(builtin_interfaces/msg/Time data
)RB"},
    {R"RB(std_msgs/msg/UInt16)RB", R"RB(uint16 data
)RB"},
    {R"RB(std_msgs/msg/UInt16MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
uint16[] data
)RB"},
    {R"RB(std_msgs/msg/UInt32)RB", R"RB(uint32 data
)RB"},
    {R"RB(std_msgs/msg/UInt32MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
uint32[] data
)RB"},
    {R"RB(std_msgs/msg/UInt64)RB", R"RB(uint64 data
)RB"},
    {R"RB(std_msgs/msg/UInt64MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
uint64[] data
)RB"},
    {R"RB(std_msgs/msg/UInt8)RB", R"RB(uint8 data
)RB"},
    {R"RB(std_msgs/msg/UInt8MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
uint8[] data
)RB"},
    {R"RB(stereo_msgs/msg/DisparityImage)RB", R"RB(std_msgs/msg/Header header
sensor_msgs/msg/Image image
float32 f
float32 T
sensor_msgs/msg/RegionOfInterest valid_window
float32 min_disparity
float32 max_disparity
float32 delta_d
)RB"},
    {R"RB(trajectory_msgs/msg/JointTrajectory)RB", R"RB(std_msgs/msg/Header header
string[] joint_names
trajectory_msgs/msg/JointTrajectoryPoint[] points
)RB"},
    {R"RB(trajectory_msgs/msg/JointTrajectoryPoint)RB", R"RB(float64[] positions
float64[] velocities
float64[] accelerations
float64[] effort
builtin_interfaces/msg/Duration time_from_start
)RB"},
    {R"RB(trajectory_msgs/msg/MultiDOFJointTrajectory)RB", R"RB(std_msgs/msg/Header header
string[] joint_names
trajectory_msgs/msg/MultiDOFJointTrajectoryPoint[] points
)RB"},
    {R"RB(trajectory_msgs/msg/MultiDOFJointTrajectoryPoint)RB", R"RB(geometry_msgs/msg/Transform[] transforms
geometry_msgs/msg/Twist[] velocities
geometry_msgs/msg/Twist[] accelerations
builtin_interfaces/msg/Duration time_from_start
)RB"},
    {R"RB(visualization_msgs/msg/ImageMarker)RB", R"RB(uint8 CIRCLE=0
uint8 LINE_STRIP=1
uint8 LINE_LIST=2
uint8 POLYGON=3
uint8 POINTS=4
uint8 ADD=0
uint8 REMOVE=1
std_msgs/msg/Header header
string ns
int32 id
int32 type
int32 action
geometry_msgs/msg/Point position
float32 scale
std_msgs/msg/ColorRGBA outline_color
uint8 filled
std_msgs/msg/ColorRGBA fill_color
builtin_interfaces/msg/Duration lifetime
geometry_msgs/msg/Point[] points
std_msgs/msg/ColorRGBA[] outline_colors
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarker)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Pose pose
string name
string description
float32 scale
visualization_msgs/msg/MenuEntry[] menu_entries
visualization_msgs/msg/InteractiveMarkerControl[] controls
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerControl)RB", R"RB(uint8 INHERIT=0
uint8 FIXED=1
uint8 VIEW_FACING=2
uint8 NONE=0
uint8 MENU=1
uint8 BUTTON=2
uint8 MOVE_AXIS=3
uint8 MOVE_PLANE=4
uint8 ROTATE_AXIS=5
uint8 MOVE_ROTATE=6
uint8 MOVE_3D=7
uint8 ROTATE_3D=8
uint8 MOVE_ROTATE_3D=9
string name
geometry_msgs/msg/Quaternion orientation
uint8 orientation_mode
uint8 interaction_mode
bool always_visible
visualization_msgs/msg/Marker[] markers
bool independent_marker_orientation
string description
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerFeedback)RB", R"RB(uint8 KEEP_ALIVE=0
uint8 POSE_UPDATE=1
uint8 MENU_SELECT=2
uint8 BUTTON_CLICK=3
uint8 MOUSE_DOWN=4
uint8 MOUSE_UP=5
std_msgs/msg/Header header
string client_id
string marker_name
string control_name
uint8 event_type
geometry_msgs/msg/Pose pose
uint32 menu_entry_id
geometry_msgs/msg/Point mouse_point
bool mouse_point_valid
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerInit)RB", R"RB(string server_id
uint64 seq_num
visualization_msgs/msg/InteractiveMarker[] markers
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerPose)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Pose pose
string name
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerUpdate)RB", R"RB(uint8 KEEP_ALIVE=0
uint8 UPDATE=1
string server_id
uint64 seq_num
uint8 type
visualization_msgs/msg/InteractiveMarker[] markers
visualization_msgs/msg/InteractiveMarkerPose[] poses
string[] erases
)RB"},
    {R"RB(visualization_msgs/msg/Marker)RB", R"RB(uint8 ARROW=0
uint8 CUBE=1
uint8 SPHERE=2
uint8 CYLINDER=3
uint8 LINE_STRIP=4
uint8 LINE_LIST=5
uint8 CUBE_LIST=6
uint8 SPHERE_LIST=7
uint8 POINTS=8
uint8 TEXT_VIEW_FACING=9
uint8 MESH_RESOURCE=10
uint8 TRIANGLE_LIST=11
uint8 ADD=0
uint8 MODIFY=0
uint8 DELETE=2
uint8 DELETEALL=3
std_msgs/msg/Header header
string ns
int32 id
int32 type
int32 action
geometry_msgs/msg/Pose pose
geometry_msgs/msg/Vector3 scale
std_msgs/msg/ColorRGBA color
builtin_interfaces/msg/Duration lifetime
bool frame_locked
geometry_msgs/msg/Point[] points
std_msgs/msg/ColorRGBA[] colors
string text
string mesh_resource
bool mesh_use_embedded_materials
)RB"},
    {R"RB(visualization_msgs/msg/MarkerArray)RB", R"RB(visualization_msgs/msg/Marker[] markers
)RB"},
    {R"RB(visualization_msgs/msg/MenuEntry)RB", R"RB(uint8 FEEDBACK=0
uint8 ROSRUN=1
uint8 ROSLAUNCH=2
uint32 id
uint32 parent_id
string title
string command
uint8 command_type
)RB"},
};

const GeneratedTypeDefinition kRos2DashingTypes[] = {
    {R"RB(action_msgs/msg/GoalInfo)RB", R"RB(unique_identifier_msgs/msg/UUID goal_id
builtin_interfaces/msg/Time stamp
)RB"},
    {R"RB(action_msgs/msg/GoalStatus)RB", R"RB(int8 STATUS_UNKNOWN=0
int8 STATUS_ACCEPTED=1
int8 STATUS_EXECUTING=2
int8 STATUS_CANCELING=3
int8 STATUS_SUCCEEDED=4
int8 STATUS_CANCELED=5
int8 STATUS_ABORTED=6
action_msgs/msg/GoalInfo goal_info
int8 status
)RB"},
    {R"RB(action_msgs/msg/GoalStatusArray)RB", R"RB(action_msgs/msg/GoalStatus[] status_list
)RB"},
    {R"RB(actionlib_msgs/msg/GoalID)RB", R"RB(builtin_interfaces/msg/Time stamp
string id
)RB"},
    {R"RB(actionlib_msgs/msg/GoalStatus)RB", R"RB(uint8 PENDING=0
uint8 ACTIVE=1
uint8 PREEMPTED=2
uint8 SUCCEEDED=3
uint8 ABORTED=4
uint8 REJECTED=5
uint8 PREEMPTING=6
uint8 RECALLING=7
uint8 RECALLED=8
uint8 LOST=9
actionlib_msgs/msg/GoalID goal_id
uint8 status
string text
)RB"},
    {R"RB(actionlib_msgs/msg/GoalStatusArray)RB", R"RB(std_msgs/msg/Header header
actionlib_msgs/msg/GoalStatus[] status_list
)RB"},
    {R"RB(builtin_interfaces/msg/Duration)RB", R"RB(int32 sec
uint32 nanosec
)RB"},
    {R"RB(builtin_interfaces/msg/Time)RB", R"RB(int32 sec
uint32 nanosec
)RB"},
    {R"RB(diagnostic_msgs/msg/DiagnosticArray)RB", R"RB(std_msgs/msg/Header header
diagnostic_msgs/msg/DiagnosticStatus[] status
)RB"},
    {R"RB(diagnostic_msgs/msg/DiagnosticStatus)RB", R"RB(byte OK=0
byte WARN=1
byte ERROR=2
byte STALE=3
byte level
string name
string message
string hardware_id
diagnostic_msgs/msg/KeyValue[] values
)RB"},
    {R"RB(diagnostic_msgs/msg/KeyValue)RB", R"RB(string key
string value
)RB"},
    {R"RB(geometry_msgs/msg/Accel)RB", R"RB(geometry_msgs/msg/Vector3 linear
geometry_msgs/msg/Vector3 angular
)RB"},
    {R"RB(geometry_msgs/msg/AccelStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Accel accel
)RB"},
    {R"RB(geometry_msgs/msg/AccelWithCovariance)RB", R"RB(geometry_msgs/msg/Accel accel
float64[36] covariance
)RB"},
    {R"RB(geometry_msgs/msg/AccelWithCovarianceStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/AccelWithCovariance accel
)RB"},
    {R"RB(geometry_msgs/msg/Inertia)RB", R"RB(float64 m
geometry_msgs/msg/Vector3 com
float64 ixx
float64 ixy
float64 ixz
float64 iyy
float64 iyz
float64 izz
)RB"},
    {R"RB(geometry_msgs/msg/InertiaStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Inertia inertia
)RB"},
    {R"RB(geometry_msgs/msg/Point)RB", R"RB(float64 x
float64 y
float64 z
)RB"},
    {R"RB(geometry_msgs/msg/Point32)RB", R"RB(float32 x
float32 y
float32 z
)RB"},
    {R"RB(geometry_msgs/msg/PointStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Point point
)RB"},
    {R"RB(geometry_msgs/msg/Polygon)RB", R"RB(geometry_msgs/msg/Point32[] points
)RB"},
    {R"RB(geometry_msgs/msg/PolygonStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Polygon polygon
)RB"},
    {R"RB(geometry_msgs/msg/Pose)RB", R"RB(geometry_msgs/msg/Point position
geometry_msgs/msg/Quaternion orientation
)RB"},
    {R"RB(geometry_msgs/msg/Pose2D)RB", R"RB(float64 x
float64 y
float64 theta
)RB"},
    {R"RB(geometry_msgs/msg/PoseArray)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Pose[] poses
)RB"},
    {R"RB(geometry_msgs/msg/PoseStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Pose pose
)RB"},
    {R"RB(geometry_msgs/msg/PoseWithCovariance)RB", R"RB(geometry_msgs/msg/Pose pose
float64[36] covariance
)RB"},
    {R"RB(geometry_msgs/msg/PoseWithCovarianceStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/PoseWithCovariance pose
)RB"},
    {R"RB(geometry_msgs/msg/Quaternion)RB", R"RB(float64 x
float64 y
float64 z
float64 w
)RB"},
    {R"RB(geometry_msgs/msg/QuaternionStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Quaternion quaternion
)RB"},
    {R"RB(geometry_msgs/msg/Transform)RB", R"RB(geometry_msgs/msg/Vector3 translation
geometry_msgs/msg/Quaternion rotation
)RB"},
    {R"RB(geometry_msgs/msg/TransformStamped)RB", R"RB(std_msgs/msg/Header header
string child_frame_id
geometry_msgs/msg/Transform transform
)RB"},
    {R"RB(geometry_msgs/msg/Twist)RB", R"RB(geometry_msgs/msg/Vector3 linear
geometry_msgs/msg/Vector3 angular
)RB"},
    {R"RB(geometry_msgs/msg/TwistStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Twist twist
)RB"},
    {R"RB(geometry_msgs/msg/TwistWithCovariance)RB", R"RB(geometry_msgs/msg/Twist twist
float64[36] covariance
)RB"},
    {R"RB(geometry_msgs/msg/TwistWithCovarianceStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/TwistWithCovariance twist
)RB"},
    {R"RB(geometry_msgs/msg/Vector3)RB", R"RB(float64 x
float64 y
float64 z
)RB"},
    {R"RB(geometry_msgs/msg/Vector3Stamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Vector3 vector
)RB"},
    {R"RB(geometry_msgs/msg/Wrench)RB", R"RB(geometry_msgs/msg/Vector3 force
geometry_msgs/msg/Vector3 torque
)RB"},
    {R"RB(geometry_msgs/msg/WrenchStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Wrench wrench
)RB"},
    {R"RB(lifecycle_msgs/msg/State)RB", R"RB(uint8 PRIMARY_STATE_UNKNOWN=0
uint8 PRIMARY_STATE_UNCONFIGURED=1
uint8 PRIMARY_STATE_INACTIVE=2
uint8 PRIMARY_STATE_ACTIVE=3
uint8 PRIMARY_STATE_FINALIZED=4
uint8 TRANSITION_STATE_CONFIGURING=10
uint8 TRANSITION_STATE_CLEANINGUP=11
uint8 TRANSITION_STATE_SHUTTINGDOWN=12
uint8 TRANSITION_STATE_ACTIVATING=13
uint8 TRANSITION_STATE_DEACTIVATING=14
uint8 TRANSITION_STATE_ERRORPROCESSING=15
uint8 id
string label
)RB"},
    {R"RB(lifecycle_msgs/msg/Transition)RB", R"RB(uint8 TRANSITION_CREATE=0
uint8 TRANSITION_CONFIGURE=1
uint8 TRANSITION_CLEANUP=2
uint8 TRANSITION_ACTIVATE=3
uint8 TRANSITION_DEACTIVATE=4
uint8 TRANSITION_UNCONFIGURED_SHUTDOWN=5
uint8 TRANSITION_INACTIVE_SHUTDOWN=6
uint8 TRANSITION_ACTIVE_SHUTDOWN=7
uint8 TRANSITION_DESTROY=8
uint8 TRANSITION_ON_CONFIGURE_SUCCESS=10
uint8 TRANSITION_ON_CONFIGURE_FAILURE=11
uint8 TRANSITION_ON_CONFIGURE_ERROR=12
uint8 TRANSITION_ON_CLEANUP_SUCCESS=20
uint8 TRANSITION_ON_CLEANUP_FAILURE=21
uint8 TRANSITION_ON_CLEANUP_ERROR=22
uint8 TRANSITION_ON_ACTIVATE_SUCCESS=30
uint8 TRANSITION_ON_ACTIVATE_FAILURE=31
uint8 TRANSITION_ON_ACTIVATE_ERROR=32
uint8 TRANSITION_ON_DEACTIVATE_SUCCESS=40
uint8 TRANSITION_ON_DEACTIVATE_FAILURE=41
uint8 TRANSITION_ON_DEACTIVATE_ERROR=42
uint8 TRANSITION_ON_SHUTDOWN_SUCCESS=50
uint8 TRANSITION_ON_SHUTDOWN_FAILURE=51
uint8 TRANSITION_ON_SHUTDOWN_ERROR=52
uint8 TRANSITION_ON_ERROR_SUCCESS=60
uint8 TRANSITION_ON_ERROR_FAILURE=61
uint8 TRANSITION_ON_ERROR_ERROR=62
uint8 TRANSITION_CALLBACK_SUCCESS=97
uint8 TRANSITION_CALLBACK_FAILURE=98
uint8 TRANSITION_CALLBACK_ERROR=99
uint8 id
string label
)RB"},
    {R"RB(lifecycle_msgs/msg/TransitionDescription)RB", R"RB(lifecycle_msgs/msg/Transition transition
lifecycle_msgs/msg/State start_state
lifecycle_msgs/msg/State goal_state
)RB"},
    {R"RB(lifecycle_msgs/msg/TransitionEvent)RB", R"RB(uint64 timestamp
lifecycle_msgs/msg/Transition transition
lifecycle_msgs/msg/State start_state
lifecycle_msgs/msg/State goal_state
)RB"},
    {R"RB(nav_msgs/msg/GridCells)RB", R"RB(std_msgs/msg/Header header
float32 cell_width
float32 cell_height
geometry_msgs/msg/Point[] cells
)RB"},
    {R"RB(nav_msgs/msg/MapMetaData)RB", R"RB(builtin_interfaces/msg/Time map_load_time
float32 resolution
uint32 width
uint32 height
geometry_msgs/msg/Pose origin
)RB"},
    {R"RB(nav_msgs/msg/OccupancyGrid)RB", R"RB(std_msgs/msg/Header header
nav_msgs/msg/MapMetaData info
int8[] data
)RB"},
    {R"RB(nav_msgs/msg/Odometry)RB", R"RB(std_msgs/msg/Header header
string child_frame_id
geometry_msgs/msg/PoseWithCovariance pose
geometry_msgs/msg/TwistWithCovariance twist
)RB"},
    {R"RB(nav_msgs/msg/Path)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/PoseStamped[] poses
)RB"},
    {R"RB(rcl_interfaces/msg/FloatingPointRange)RB", R"RB(float64 from_value
float64 to_value
float64 step
)RB"},
    {R"RB(rcl_interfaces/msg/IntegerRange)RB", R"RB(int64 from_value
int64 to_value
uint64 step
)RB"},
    {R"RB(rcl_interfaces/msg/IntraProcessMessage)RB", R"RB(uint64 publisher_id
uint64 message_sequence
)RB"},
    {R"RB(rcl_interfaces/msg/ListParametersResult)RB", R"RB(string[] names
string[] prefixes
)RB"},
    {R"RB(rcl_interfaces/msg/Log)RB", R"RB(byte DEBUG=10
byte INFO=20
byte WARN=30
byte ERROR=40
byte FATAL=50
builtin_interfaces/msg/Time stamp
uint8 level
string name
string msg
string file
string function
uint32 line
)RB"},
    {R"RB(rcl_interfaces/msg/Parameter)RB", R"RB(string name
rcl_interfaces/msg/ParameterValue value
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterDescriptor)RB", R"RB(string name
uint8 type
string description
string additional_constraints
bool read_only
rcl_interfaces/msg/FloatingPointRange[<=1] floating_point_range
rcl_interfaces/msg/IntegerRange[<=1] integer_range
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterEvent)RB", R"RB(builtin_interfaces/msg/Time stamp
string node
rcl_interfaces/msg/Parameter[] new_parameters
rcl_interfaces/msg/Parameter[] changed_parameters
rcl_interfaces/msg/Parameter[] deleted_parameters
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterEventDescriptors)RB", R"RB(rcl_interfaces/msg/ParameterDescriptor[] new_parameters
rcl_interfaces/msg/ParameterDescriptor[] changed_parameters
rcl_interfaces/msg/ParameterDescriptor[] deleted_parameters
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterType)RB", R"RB(uint8 PARAMETER_NOT_SET=0
uint8 PARAMETER_BOOL=1
uint8 PARAMETER_INTEGER=2
uint8 PARAMETER_DOUBLE=3
uint8 PARAMETER_STRING=4
uint8 PARAMETER_BYTE_ARRAY=5
uint8 PARAMETER_BOOL_ARRAY=6
uint8 PARAMETER_INTEGER_ARRAY=7
uint8 PARAMETER_DOUBLE_ARRAY=8
uint8 PARAMETER_STRING_ARRAY=9
uint8 structure_needs_at_least_one_member
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterValue)RB", R"RB(uint8 type
bool bool_value
int64 integer_value
float64 double_value
string string_value
byte[] byte_array_value
bool[] bool_array_value
int64[] integer_array_value
float64[] double_array_value
string[] string_array_value
)RB"},
    {R"RB(rcl_interfaces/msg/SetParametersResult)RB", R"RB(bool successful
string reason
)RB"},
    {R"RB(rosgraph_msgs/msg/Clock)RB", R"RB(builtin_interfaces/msg/Time clock
)RB"},
    {R"RB(sensor_msgs/msg/BatteryState)RB", R"RB(uint8 POWER_SUPPLY_STATUS_UNKNOWN=0
uint8 POWER_SUPPLY_STATUS_CHARGING=1
uint8 POWER_SUPPLY_STATUS_DISCHARGING=2
uint8 POWER_SUPPLY_STATUS_NOT_CHARGING=3
uint8 POWER_SUPPLY_STATUS_FULL=4
uint8 POWER_SUPPLY_HEALTH_UNKNOWN=0
uint8 POWER_SUPPLY_HEALTH_GOOD=1
uint8 POWER_SUPPLY_HEALTH_OVERHEAT=2
uint8 POWER_SUPPLY_HEALTH_DEAD=3
uint8 POWER_SUPPLY_HEALTH_OVERVOLTAGE=4
uint8 POWER_SUPPLY_HEALTH_UNSPEC_FAILURE=5
uint8 POWER_SUPPLY_HEALTH_COLD=6
uint8 POWER_SUPPLY_HEALTH_WATCHDOG_TIMER_EXPIRE=7
uint8 POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE=8
uint8 POWER_SUPPLY_TECHNOLOGY_UNKNOWN=0
uint8 POWER_SUPPLY_TECHNOLOGY_NIMH=1
uint8 POWER_SUPPLY_TECHNOLOGY_LION=2
uint8 POWER_SUPPLY_TECHNOLOGY_LIPO=3
uint8 POWER_SUPPLY_TECHNOLOGY_LIFE=4
uint8 POWER_SUPPLY_TECHNOLOGY_NICD=5
uint8 POWER_SUPPLY_TECHNOLOGY_LIMN=6
std_msgs/msg/Header header
float32 voltage
float32 temperature
float32 current
float32 charge
float32 capacity
float32 design_capacity
float32 percentage
uint8 power_supply_status
uint8 power_supply_health
uint8 power_supply_technology
bool present
float32[] cell_voltage
float32[] cell_temperature
string location
string serial_number
)RB"},
    {R"RB(sensor_msgs/msg/CameraInfo)RB", R"RB(std_msgs/msg/Header header
uint32 height
uint32 width
string distortion_model
float64[] d
float64[9] k
float64[9] r
float64[12] p
uint32 binning_x
uint32 binning_y
sensor_msgs/msg/RegionOfInterest roi
)RB"},
    {R"RB(sensor_msgs/msg/ChannelFloat32)RB", R"RB(string name
float32[] values
)RB"},
    {R"RB(sensor_msgs/msg/CompressedImage)RB", R"RB(std_msgs/msg/Header header
string format
uint8[] data
)RB"},
    {R"RB(sensor_msgs/msg/FluidPressure)RB", R"RB(std_msgs/msg/Header header
float64 fluid_pressure
float64 variance
)RB"},
    {R"RB(sensor_msgs/msg/Illuminance)RB", R"RB(std_msgs/msg/Header header
float64 illuminance
float64 variance
)RB"},
    {R"RB(sensor_msgs/msg/Image)RB", R"RB(std_msgs/msg/Header header
uint32 height
uint32 width
string encoding
uint8 is_bigendian
uint32 step
uint8[] data
)RB"},
    {R"RB(sensor_msgs/msg/Imu)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Quaternion orientation
float64[9] orientation_covariance
geometry_msgs/msg/Vector3 angular_velocity
float64[9] angular_velocity_covariance
geometry_msgs/msg/Vector3 linear_acceleration
float64[9] linear_acceleration_covariance
)RB"},
    {R"RB(sensor_msgs/msg/JointState)RB", R"RB(std_msgs/msg/Header header
string[] name
float64[] position
float64[] velocity
float64[] effort
)RB"},
    {R"RB(sensor_msgs/msg/Joy)RB", R"RB(std_msgs/msg/Header header
float32[] axes
int32[] buttons
)RB"},
    {R"RB(sensor_msgs/msg/JoyFeedback)RB", R"RB(uint8 TYPE_LED=0
uint8 TYPE_RUMBLE=1
uint8 TYPE_BUZZER=2
uint8 type
uint8 id
float32 intensity
)RB"},
    {R"RB(sensor_msgs/msg/JoyFeedbackArray)RB", R"RB(sensor_msgs/msg/JoyFeedback[] array
)RB"},
    {R"RB(sensor_msgs/msg/LaserEcho)RB", R"RB(float32[] echoes
)RB"},
    {R"RB(sensor_msgs/msg/LaserScan)RB", R"RB(std_msgs/msg/Header header
float32 angle_min
float32 angle_max
float32 angle_increment
float32 time_increment
float32 scan_time
float32 range_min
float32 range_max
float32[] ranges
float32[] intensities
)RB"},
    {R"RB(sensor_msgs/msg/MagneticField)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Vector3 magnetic_field
float64[9] magnetic_field_covariance
)RB"},
    {R"RB(sensor_msgs/msg/MultiDOFJointState)RB", R"RB(std_msgs/msg/Header header
string[] joint_names
geometry_msgs/msg/Transform[] transforms
geometry_msgs/msg/Twist[] twist
geometry_msgs/msg/Wrench[] wrench
)RB"},
    {R"RB(sensor_msgs/msg/MultiEchoLaserScan)RB", R"RB(std_msgs/msg/Header header
float32 angle_min
float32 angle_max
float32 angle_increment
float32 time_increment
float32 scan_time
float32 range_min
float32 range_max
sensor_msgs/msg/LaserEcho[] ranges
sensor_msgs/msg/LaserEcho[] intensities
)RB"},
    {R"RB(sensor_msgs/msg/NavSatFix)RB", R"RB(uint8 COVARIANCE_TYPE_UNKNOWN=0
uint8 COVARIANCE_TYPE_APPROXIMATED=1
uint8 COVARIANCE_TYPE_DIAGONAL_KNOWN=2
uint8 COVARIANCE_TYPE_KNOWN=3
std_msgs/msg/Header header
sensor_msgs/msg/NavSatStatus status
float64 latitude
float64 longitude
float64 altitude
float64[9] position_covariance
uint8 position_covariance_type
)RB"},
    {R"RB(sensor_msgs/msg/NavSatStatus)RB", R"RB(int8 STATUS_NO_FIX=-1
int8 STATUS_FIX=0
int8 STATUS_SBAS_FIX=1
int8 STATUS_GBAS_FIX=2
uint16 SERVICE_GPS=1
uint16 SERVICE_GLONASS=2
uint16 SERVICE_COMPASS=4
uint16 SERVICE_GALILEO=8
int8 status
uint16 service
)RB"},
    {R"RB(sensor_msgs/msg/PointCloud)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Point32[] points
sensor_msgs/msg/ChannelFloat32[] channels
)RB"},
    {R"RB(sensor_msgs/msg/PointCloud2)RB", R"RB(std_msgs/msg/Header header
uint32 height
uint32 width
sensor_msgs/msg/PointField[] fields
bool is_bigendian
uint32 point_step
uint32 row_step
uint8[] data
bool is_dense
)RB"},
    {R"RB(sensor_msgs/msg/PointField)RB", R"RB(uint8 INT8=1
uint8 UINT8=2
uint8 INT16=3
uint8 UINT16=4
uint8 INT32=5
uint8 UINT32=6
uint8 FLOAT32=7
uint8 FLOAT64=8
string name
uint32 offset
uint8 datatype
uint32 count
)RB"},
    {R"RB(sensor_msgs/msg/Range)RB", R"RB(uint8 ULTRASOUND=0
uint8 INFRARED=1
std_msgs/msg/Header header
uint8 radiation_type
float32 field_of_view
float32 min_range
float32 max_range
float32 range
)RB"},
    {R"RB(sensor_msgs/msg/RegionOfInterest)RB", R"RB(uint32 x_offset
uint32 y_offset
uint32 height
uint32 width
bool do_rectify
)RB"},
    {R"RB(sensor_msgs/msg/RelativeHumidity)RB", R"RB(std_msgs/msg/Header header
float64 relative_humidity
float64 variance
)RB"},
    {R"RB(sensor_msgs/msg/Temperature)RB", R"RB(std_msgs/msg/Header header
float64 temperature
float64 variance
)RB"},
    {R"RB(sensor_msgs/msg/TimeReference)RB", R"RB(std_msgs/msg/Header header
builtin_interfaces/msg/Time time_ref
string source
)RB"},
    {R"RB(shape_msgs/msg/Mesh)RB", R"RB(shape_msgs/msg/MeshTriangle[] triangles
geometry_msgs/msg/Point[] vertices
)RB"},
    {R"RB(shape_msgs/msg/MeshTriangle)RB", R"RB(uint32[3] vertex_indices
)RB"},
    {R"RB(shape_msgs/msg/Plane)RB", R"RB(float64[4] coef
)RB"},
    {R"RB(shape_msgs/msg/SolidPrimitive)RB", R"RB(uint8 BOX=1
uint8 SPHERE=2
uint8 CYLINDER=3
uint8 CONE=4
uint8 BOX_X=0
uint8 BOX_Y=1
uint8 BOX_Z=2
uint8 SPHERE_RADIUS=0
uint8 CYLINDER_HEIGHT=0
uint8 CYLINDER_RADIUS=1
uint8 CONE_HEIGHT=0
uint8 CONE_RADIUS=1
uint8 type
float64[<=3] dimensions
)RB"},
    {R"RB(std_msgs/msg/Bool)RB", R"RB(bool data
)RB"},
    {R"RB(std_msgs/msg/Byte)RB", R"RB(byte data
)RB"},
    {R"RB(std_msgs/msg/ByteMultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
byte[] data
)RB"},
    {R"RB(std_msgs/msg/Char)RB", R"RB(char data
)RB"},
    {R"RB(std_msgs/msg/ColorRGBA)RB", R"RB(float32 r
float32 g
float32 b
float32 a
)RB"},
    {R"RB(std_msgs/msg/Empty)RB", R"RB(uint8 structure_needs_at_least_one_member
)RB"},
    {R"RB(std_msgs/msg/Float32)RB", R"RB(float32 data
)RB"},
    {R"RB(std_msgs/msg/Float32MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
float32[] data
)RB"},
    {R"RB(std_msgs/msg/Float64)RB", R"RB(float64 data
)RB"},
    {R"RB(std_msgs/msg/Float64MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
float64[] data
)RB"},
    {R"RB(std_msgs/msg/Header)RB", R"RB(builtin_interfaces/msg/Time stamp
string frame_id
)RB"},
    {R"RB(std_msgs/msg/Int16)RB", R"RB(int16 data
)RB"},
    {R"RB(std_msgs/msg/Int16MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
int16[] data
)RB"},
    {R"RB(std_msgs/msg/Int32)RB", R"RB(int32 data
)RB"},
    {R"RB(std_msgs/msg/Int32MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
int32[] data
)RB"},
    {R"RB(std_msgs/msg/Int64)RB", R"RB(int64 data
)RB"},
    {R"RB(std_msgs/msg/Int64MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
int64[] data
)RB"},
    {R"RB(std_msgs/msg/Int8)RB", R"RB(int8 data
)RB"},
    {R"RB(std_msgs/msg/Int8MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
int8[] data
)RB"},
    {R"RB(std_msgs/msg/MultiArrayDimension)RB", R"RB(string label
uint32 size
uint32 stride
)RB"},
    {R"RB(std_msgs/msg/MultiArrayLayout)RB", R"RB(std_msgs/msg/MultiArrayDimension[] dim
uint32 data_offset
)RB"},
    {R"RB(std_msgs/msg/String)RB", R"RB(string data
)RB"},
    {R"RB(std_msgs/msg/UInt16)RB", R"RB(uint16 data
)RB"},
    {R"RB(std_msgs/msg/UInt16MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
uint16[] data
)RB"},
    {R"RB(std_msgs/msg/UInt32)RB", R"RB(uint32 data
)RB"},
    {R"RB(std_msgs/msg/UInt32MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
uint32[] data
)RB"},
    {R"RB(std_msgs/msg/UInt64)RB", R"RB(uint64 data
)RB"},
    {R"RB(std_msgs/msg/UInt64MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
uint64[] data
)RB"},
    {R"RB(std_msgs/msg/UInt8)RB", R"RB(uint8 data
)RB"},
    {R"RB(std_msgs/msg/UInt8MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
uint8[] data
)RB"},
    {R"RB(stereo_msgs/msg/DisparityImage)RB", R"RB(std_msgs/msg/Header header
sensor_msgs/msg/Image image
float32 f
float32 t
sensor_msgs/msg/RegionOfInterest valid_window
float32 min_disparity
float32 max_disparity
float32 delta_d
)RB"},
    {R"RB(tf2_msgs/msg/TF2Error)RB", R"RB(uint8 NO_ERROR=0
uint8 LOOKUP_ERROR=1
uint8 CONNECTIVITY_ERROR=2
uint8 EXTRAPOLATION_ERROR=3
uint8 INVALID_ARGUMENT_ERROR=4
uint8 TIMEOUT_ERROR=5
uint8 TRANSFORM_ERROR=6
uint8 error
string error_string
)RB"},
    {R"RB(tf2_msgs/msg/TFMessage)RB", R"RB(geometry_msgs/msg/TransformStamped[] transforms
)RB"},
    {R"RB(trajectory_msgs/msg/JointTrajectory)RB", R"RB(std_msgs/msg/Header header
string[] joint_names
trajectory_msgs/msg/JointTrajectoryPoint[] points
)RB"},
    {R"RB(trajectory_msgs/msg/JointTrajectoryPoint)RB", R"RB(float64[] positions
float64[] velocities
float64[] accelerations
float64[] effort
builtin_interfaces/msg/Duration time_from_start
)RB"},
    {R"RB(trajectory_msgs/msg/MultiDOFJointTrajectory)RB", R"RB(std_msgs/msg/Header header
string[] joint_names
trajectory_msgs/msg/MultiDOFJointTrajectoryPoint[] points
)RB"},
    {R"RB(trajectory_msgs/msg/MultiDOFJointTrajectoryPoint)RB", R"RB(geometry_msgs/msg/Transform[] transforms
geometry_msgs/msg/Twist[] velocities
geometry_msgs/msg/Twist[] accelerations
builtin_interfaces/msg/Duration time_from_start
)RB"},
    {R"RB(unique_identifier_msgs/msg/UUID)RB", R"RB(uint8[16] uuid
)RB"},
    {R"RB(visualization_msgs/msg/ImageMarker)RB", R"RB(uint8 CIRCLE=0
uint8 LINE_STRIP=1
uint8 LINE_LIST=2
uint8 POLYGON=3
uint8 POINTS=4
uint8 ADD=0
uint8 REMOVE=1
std_msgs/msg/Header header
string ns
int32 id
int32 type
int32 action
geometry_msgs/msg/Point position
float32 scale
std_msgs/msg/ColorRGBA outline_color
uint8 filled
std_msgs/msg/ColorRGBA fill_color
builtin_interfaces/msg/Duration lifetime
geometry_msgs/msg/Point[] points
std_msgs/msg/ColorRGBA[] outline_colors
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarker)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Pose pose
string name
string description
float32 scale
visualization_msgs/msg/MenuEntry[] menu_entries
visualization_msgs/msg/InteractiveMarkerControl[] controls
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerControl)RB", R"RB(uint8 INHERIT=0
uint8 FIXED=1
uint8 VIEW_FACING=2
uint8 NONE=0
uint8 MENU=1
uint8 BUTTON=2
uint8 MOVE_AXIS=3
uint8 MOVE_PLANE=4
uint8 ROTATE_AXIS=5
uint8 MOVE_ROTATE=6
uint8 MOVE_3D=7
uint8 ROTATE_3D=8
uint8 MOVE_ROTATE_3D=9
string name
geometry_msgs/msg/Quaternion orientation
uint8 orientation_mode
uint8 interaction_mode
bool always_visible
visualization_msgs/msg/Marker[] markers
bool independent_marker_orientation
string description
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerFeedback)RB", R"RB(uint8 KEEP_ALIVE=0
uint8 POSE_UPDATE=1
uint8 MENU_SELECT=2
uint8 BUTTON_CLICK=3
uint8 MOUSE_DOWN=4
uint8 MOUSE_UP=5
std_msgs/msg/Header header
string client_id
string marker_name
string control_name
uint8 event_type
geometry_msgs/msg/Pose pose
uint32 menu_entry_id
geometry_msgs/msg/Point mouse_point
bool mouse_point_valid
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerInit)RB", R"RB(string server_id
uint64 seq_num
visualization_msgs/msg/InteractiveMarker[] markers
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerPose)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Pose pose
string name
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerUpdate)RB", R"RB(uint8 KEEP_ALIVE=0
uint8 UPDATE=1
string server_id
uint64 seq_num
uint8 type
visualization_msgs/msg/InteractiveMarker[] markers
visualization_msgs/msg/InteractiveMarkerPose[] poses
string[] erases
)RB"},
    {R"RB(visualization_msgs/msg/Marker)RB", R"RB(uint8 ARROW=0
uint8 CUBE=1
uint8 SPHERE=2
uint8 CYLINDER=3
uint8 LINE_STRIP=4
uint8 LINE_LIST=5
uint8 CUBE_LIST=6
uint8 SPHERE_LIST=7
uint8 POINTS=8
uint8 TEXT_VIEW_FACING=9
uint8 MESH_RESOURCE=10
uint8 TRIANGLE_LIST=11
uint8 ADD=0
uint8 MODIFY=0
uint8 DELETE=2
uint8 DELETEALL=3
std_msgs/msg/Header header
string ns
int32 id
int32 type
int32 action
geometry_msgs/msg/Pose pose
geometry_msgs/msg/Vector3 scale
std_msgs/msg/ColorRGBA color
builtin_interfaces/msg/Duration lifetime
bool frame_locked
geometry_msgs/msg/Point[] points
std_msgs/msg/ColorRGBA[] colors
string text
string mesh_resource
bool mesh_use_embedded_materials
)RB"},
    {R"RB(visualization_msgs/msg/MarkerArray)RB", R"RB(visualization_msgs/msg/Marker[] markers
)RB"},
    {R"RB(visualization_msgs/msg/MenuEntry)RB", R"RB(uint8 FEEDBACK=0
uint8 ROSRUN=1
uint8 ROSLAUNCH=2
uint32 id
uint32 parent_id
string title
string command
uint8 command_type
)RB"},
};

const GeneratedTypeDefinition kRos2EloquentTypes[] = {
    {R"RB(action_msgs/msg/GoalInfo)RB", R"RB(unique_identifier_msgs/msg/UUID goal_id
builtin_interfaces/msg/Time stamp
)RB"},
    {R"RB(action_msgs/msg/GoalStatus)RB", R"RB(int8 STATUS_UNKNOWN=0
int8 STATUS_ACCEPTED=1
int8 STATUS_EXECUTING=2
int8 STATUS_CANCELING=3
int8 STATUS_SUCCEEDED=4
int8 STATUS_CANCELED=5
int8 STATUS_ABORTED=6
action_msgs/msg/GoalInfo goal_info
int8 status
)RB"},
    {R"RB(action_msgs/msg/GoalStatusArray)RB", R"RB(action_msgs/msg/GoalStatus[] status_list
)RB"},
    {R"RB(actionlib_msgs/msg/GoalID)RB", R"RB(builtin_interfaces/msg/Time stamp
string id
)RB"},
    {R"RB(actionlib_msgs/msg/GoalStatus)RB", R"RB(uint8 PENDING=0
uint8 ACTIVE=1
uint8 PREEMPTED=2
uint8 SUCCEEDED=3
uint8 ABORTED=4
uint8 REJECTED=5
uint8 PREEMPTING=6
uint8 RECALLING=7
uint8 RECALLED=8
uint8 LOST=9
actionlib_msgs/msg/GoalID goal_id
uint8 status
string text
)RB"},
    {R"RB(actionlib_msgs/msg/GoalStatusArray)RB", R"RB(std_msgs/msg/Header header
actionlib_msgs/msg/GoalStatus[] status_list
)RB"},
    {R"RB(builtin_interfaces/msg/Duration)RB", R"RB(int32 sec
uint32 nanosec
)RB"},
    {R"RB(builtin_interfaces/msg/Time)RB", R"RB(int32 sec
uint32 nanosec
)RB"},
    {R"RB(diagnostic_msgs/msg/DiagnosticArray)RB", R"RB(std_msgs/msg/Header header
diagnostic_msgs/msg/DiagnosticStatus[] status
)RB"},
    {R"RB(diagnostic_msgs/msg/DiagnosticStatus)RB", R"RB(byte OK=0
byte WARN=1
byte ERROR=2
byte STALE=3
byte level
string name
string message
string hardware_id
diagnostic_msgs/msg/KeyValue[] values
)RB"},
    {R"RB(diagnostic_msgs/msg/KeyValue)RB", R"RB(string key
string value
)RB"},
    {R"RB(geometry_msgs/msg/Accel)RB", R"RB(geometry_msgs/msg/Vector3 linear
geometry_msgs/msg/Vector3 angular
)RB"},
    {R"RB(geometry_msgs/msg/AccelStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Accel accel
)RB"},
    {R"RB(geometry_msgs/msg/AccelWithCovariance)RB", R"RB(geometry_msgs/msg/Accel accel
float64[36] covariance
)RB"},
    {R"RB(geometry_msgs/msg/AccelWithCovarianceStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/AccelWithCovariance accel
)RB"},
    {R"RB(geometry_msgs/msg/Inertia)RB", R"RB(float64 m
geometry_msgs/msg/Vector3 com
float64 ixx
float64 ixy
float64 ixz
float64 iyy
float64 iyz
float64 izz
)RB"},
    {R"RB(geometry_msgs/msg/InertiaStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Inertia inertia
)RB"},
    {R"RB(geometry_msgs/msg/Point)RB", R"RB(float64 x
float64 y
float64 z
)RB"},
    {R"RB(geometry_msgs/msg/Point32)RB", R"RB(float32 x
float32 y
float32 z
)RB"},
    {R"RB(geometry_msgs/msg/PointStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Point point
)RB"},
    {R"RB(geometry_msgs/msg/Polygon)RB", R"RB(geometry_msgs/msg/Point32[] points
)RB"},
    {R"RB(geometry_msgs/msg/PolygonStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Polygon polygon
)RB"},
    {R"RB(geometry_msgs/msg/Pose)RB", R"RB(geometry_msgs/msg/Point position
geometry_msgs/msg/Quaternion orientation
)RB"},
    {R"RB(geometry_msgs/msg/Pose2D)RB", R"RB(float64 x
float64 y
float64 theta
)RB"},
    {R"RB(geometry_msgs/msg/PoseArray)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Pose[] poses
)RB"},
    {R"RB(geometry_msgs/msg/PoseStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Pose pose
)RB"},
    {R"RB(geometry_msgs/msg/PoseWithCovariance)RB", R"RB(geometry_msgs/msg/Pose pose
float64[36] covariance
)RB"},
    {R"RB(geometry_msgs/msg/PoseWithCovarianceStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/PoseWithCovariance pose
)RB"},
    {R"RB(geometry_msgs/msg/Quaternion)RB", R"RB(float64 x
float64 y
float64 z
float64 w
)RB"},
    {R"RB(geometry_msgs/msg/QuaternionStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Quaternion quaternion
)RB"},
    {R"RB(geometry_msgs/msg/Transform)RB", R"RB(geometry_msgs/msg/Vector3 translation
geometry_msgs/msg/Quaternion rotation
)RB"},
    {R"RB(geometry_msgs/msg/TransformStamped)RB", R"RB(std_msgs/msg/Header header
string child_frame_id
geometry_msgs/msg/Transform transform
)RB"},
    {R"RB(geometry_msgs/msg/Twist)RB", R"RB(geometry_msgs/msg/Vector3 linear
geometry_msgs/msg/Vector3 angular
)RB"},
    {R"RB(geometry_msgs/msg/TwistStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Twist twist
)RB"},
    {R"RB(geometry_msgs/msg/TwistWithCovariance)RB", R"RB(geometry_msgs/msg/Twist twist
float64[36] covariance
)RB"},
    {R"RB(geometry_msgs/msg/TwistWithCovarianceStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/TwistWithCovariance twist
)RB"},
    {R"RB(geometry_msgs/msg/Vector3)RB", R"RB(float64 x
float64 y
float64 z
)RB"},
    {R"RB(geometry_msgs/msg/Vector3Stamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Vector3 vector
)RB"},
    {R"RB(geometry_msgs/msg/Wrench)RB", R"RB(geometry_msgs/msg/Vector3 force
geometry_msgs/msg/Vector3 torque
)RB"},
    {R"RB(geometry_msgs/msg/WrenchStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Wrench wrench
)RB"},
    {R"RB(lifecycle_msgs/msg/State)RB", R"RB(uint8 PRIMARY_STATE_UNKNOWN=0
uint8 PRIMARY_STATE_UNCONFIGURED=1
uint8 PRIMARY_STATE_INACTIVE=2
uint8 PRIMARY_STATE_ACTIVE=3
uint8 PRIMARY_STATE_FINALIZED=4
uint8 TRANSITION_STATE_CONFIGURING=10
uint8 TRANSITION_STATE_CLEANINGUP=11
uint8 TRANSITION_STATE_SHUTTINGDOWN=12
uint8 TRANSITION_STATE_ACTIVATING=13
uint8 TRANSITION_STATE_DEACTIVATING=14
uint8 TRANSITION_STATE_ERRORPROCESSING=15
uint8 id
string label
)RB"},
    {R"RB(lifecycle_msgs/msg/Transition)RB", R"RB(uint8 TRANSITION_CREATE=0
uint8 TRANSITION_CONFIGURE=1
uint8 TRANSITION_CLEANUP=2
uint8 TRANSITION_ACTIVATE=3
uint8 TRANSITION_DEACTIVATE=4
uint8 TRANSITION_UNCONFIGURED_SHUTDOWN=5
uint8 TRANSITION_INACTIVE_SHUTDOWN=6
uint8 TRANSITION_ACTIVE_SHUTDOWN=7
uint8 TRANSITION_DESTROY=8
uint8 TRANSITION_ON_CONFIGURE_SUCCESS=10
uint8 TRANSITION_ON_CONFIGURE_FAILURE=11
uint8 TRANSITION_ON_CONFIGURE_ERROR=12
uint8 TRANSITION_ON_CLEANUP_SUCCESS=20
uint8 TRANSITION_ON_CLEANUP_FAILURE=21
uint8 TRANSITION_ON_CLEANUP_ERROR=22
uint8 TRANSITION_ON_ACTIVATE_SUCCESS=30
uint8 TRANSITION_ON_ACTIVATE_FAILURE=31
uint8 TRANSITION_ON_ACTIVATE_ERROR=32
uint8 TRANSITION_ON_DEACTIVATE_SUCCESS=40
uint8 TRANSITION_ON_DEACTIVATE_FAILURE=41
uint8 TRANSITION_ON_DEACTIVATE_ERROR=42
uint8 TRANSITION_ON_SHUTDOWN_SUCCESS=50
uint8 TRANSITION_ON_SHUTDOWN_FAILURE=51
uint8 TRANSITION_ON_SHUTDOWN_ERROR=52
uint8 TRANSITION_ON_ERROR_SUCCESS=60
uint8 TRANSITION_ON_ERROR_FAILURE=61
uint8 TRANSITION_ON_ERROR_ERROR=62
uint8 TRANSITION_CALLBACK_SUCCESS=97
uint8 TRANSITION_CALLBACK_FAILURE=98
uint8 TRANSITION_CALLBACK_ERROR=99
uint8 id
string label
)RB"},
    {R"RB(lifecycle_msgs/msg/TransitionDescription)RB", R"RB(lifecycle_msgs/msg/Transition transition
lifecycle_msgs/msg/State start_state
lifecycle_msgs/msg/State goal_state
)RB"},
    {R"RB(lifecycle_msgs/msg/TransitionEvent)RB", R"RB(uint64 timestamp
lifecycle_msgs/msg/Transition transition
lifecycle_msgs/msg/State start_state
lifecycle_msgs/msg/State goal_state
)RB"},
    {R"RB(nav_msgs/msg/GridCells)RB", R"RB(std_msgs/msg/Header header
float32 cell_width
float32 cell_height
geometry_msgs/msg/Point[] cells
)RB"},
    {R"RB(nav_msgs/msg/MapMetaData)RB", R"RB(builtin_interfaces/msg/Time map_load_time
float32 resolution
uint32 width
uint32 height
geometry_msgs/msg/Pose origin
)RB"},
    {R"RB(nav_msgs/msg/OccupancyGrid)RB", R"RB(std_msgs/msg/Header header
nav_msgs/msg/MapMetaData info
int8[] data
)RB"},
    {R"RB(nav_msgs/msg/Odometry)RB", R"RB(std_msgs/msg/Header header
string child_frame_id
geometry_msgs/msg/PoseWithCovariance pose
geometry_msgs/msg/TwistWithCovariance twist
)RB"},
    {R"RB(nav_msgs/msg/Path)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/PoseStamped[] poses
)RB"},
    {R"RB(rcl_interfaces/msg/FloatingPointRange)RB", R"RB(float64 from_value
float64 to_value
float64 step
)RB"},
    {R"RB(rcl_interfaces/msg/IntegerRange)RB", R"RB(int64 from_value
int64 to_value
uint64 step
)RB"},
    {R"RB(rcl_interfaces/msg/IntraProcessMessage)RB", R"RB(uint64 publisher_id
uint64 message_sequence
)RB"},
    {R"RB(rcl_interfaces/msg/ListParametersResult)RB", R"RB(string[] names
string[] prefixes
)RB"},
    {R"RB(rcl_interfaces/msg/Log)RB", R"RB(byte DEBUG=10
byte INFO=20
byte WARN=30
byte ERROR=40
byte FATAL=50
builtin_interfaces/msg/Time stamp
uint8 level
string name
string msg
string file
string function
uint32 line
)RB"},
    {R"RB(rcl_interfaces/msg/Parameter)RB", R"RB(string name
rcl_interfaces/msg/ParameterValue value
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterDescriptor)RB", R"RB(string name
uint8 type
string description
string additional_constraints
bool read_only
rcl_interfaces/msg/FloatingPointRange[<=1] floating_point_range
rcl_interfaces/msg/IntegerRange[<=1] integer_range
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterEvent)RB", R"RB(builtin_interfaces/msg/Time stamp
string node
rcl_interfaces/msg/Parameter[] new_parameters
rcl_interfaces/msg/Parameter[] changed_parameters
rcl_interfaces/msg/Parameter[] deleted_parameters
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterEventDescriptors)RB", R"RB(rcl_interfaces/msg/ParameterDescriptor[] new_parameters
rcl_interfaces/msg/ParameterDescriptor[] changed_parameters
rcl_interfaces/msg/ParameterDescriptor[] deleted_parameters
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterType)RB", R"RB(uint8 PARAMETER_NOT_SET=0
uint8 PARAMETER_BOOL=1
uint8 PARAMETER_INTEGER=2
uint8 PARAMETER_DOUBLE=3
uint8 PARAMETER_STRING=4
uint8 PARAMETER_BYTE_ARRAY=5
uint8 PARAMETER_BOOL_ARRAY=6
uint8 PARAMETER_INTEGER_ARRAY=7
uint8 PARAMETER_DOUBLE_ARRAY=8
uint8 PARAMETER_STRING_ARRAY=9
uint8 structure_needs_at_least_one_member
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterValue)RB", R"RB(uint8 type
bool bool_value
int64 integer_value
float64 double_value
string string_value
byte[] byte_array_value
bool[] bool_array_value
int64[] integer_array_value
float64[] double_array_value
string[] string_array_value
)RB"},
    {R"RB(rcl_interfaces/msg/SetParametersResult)RB", R"RB(bool successful
string reason
)RB"},
    {R"RB(rosgraph_msgs/msg/Clock)RB", R"RB(builtin_interfaces/msg/Time clock
)RB"},
    {R"RB(sensor_msgs/msg/BatteryState)RB", R"RB(uint8 POWER_SUPPLY_STATUS_UNKNOWN=0
uint8 POWER_SUPPLY_STATUS_CHARGING=1
uint8 POWER_SUPPLY_STATUS_DISCHARGING=2
uint8 POWER_SUPPLY_STATUS_NOT_CHARGING=3
uint8 POWER_SUPPLY_STATUS_FULL=4
uint8 POWER_SUPPLY_HEALTH_UNKNOWN=0
uint8 POWER_SUPPLY_HEALTH_GOOD=1
uint8 POWER_SUPPLY_HEALTH_OVERHEAT=2
uint8 POWER_SUPPLY_HEALTH_DEAD=3
uint8 POWER_SUPPLY_HEALTH_OVERVOLTAGE=4
uint8 POWER_SUPPLY_HEALTH_UNSPEC_FAILURE=5
uint8 POWER_SUPPLY_HEALTH_COLD=6
uint8 POWER_SUPPLY_HEALTH_WATCHDOG_TIMER_EXPIRE=7
uint8 POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE=8
uint8 POWER_SUPPLY_TECHNOLOGY_UNKNOWN=0
uint8 POWER_SUPPLY_TECHNOLOGY_NIMH=1
uint8 POWER_SUPPLY_TECHNOLOGY_LION=2
uint8 POWER_SUPPLY_TECHNOLOGY_LIPO=3
uint8 POWER_SUPPLY_TECHNOLOGY_LIFE=4
uint8 POWER_SUPPLY_TECHNOLOGY_NICD=5
uint8 POWER_SUPPLY_TECHNOLOGY_LIMN=6
std_msgs/msg/Header header
float32 voltage
float32 temperature
float32 current
float32 charge
float32 capacity
float32 design_capacity
float32 percentage
uint8 power_supply_status
uint8 power_supply_health
uint8 power_supply_technology
bool present
float32[] cell_voltage
float32[] cell_temperature
string location
string serial_number
)RB"},
    {R"RB(sensor_msgs/msg/CameraInfo)RB", R"RB(std_msgs/msg/Header header
uint32 height
uint32 width
string distortion_model
float64[] d
float64[9] k
float64[9] r
float64[12] p
uint32 binning_x
uint32 binning_y
sensor_msgs/msg/RegionOfInterest roi
)RB"},
    {R"RB(sensor_msgs/msg/ChannelFloat32)RB", R"RB(string name
float32[] values
)RB"},
    {R"RB(sensor_msgs/msg/CompressedImage)RB", R"RB(std_msgs/msg/Header header
string format
uint8[] data
)RB"},
    {R"RB(sensor_msgs/msg/FluidPressure)RB", R"RB(std_msgs/msg/Header header
float64 fluid_pressure
float64 variance
)RB"},
    {R"RB(sensor_msgs/msg/Illuminance)RB", R"RB(std_msgs/msg/Header header
float64 illuminance
float64 variance
)RB"},
    {R"RB(sensor_msgs/msg/Image)RB", R"RB(std_msgs/msg/Header header
uint32 height
uint32 width
string encoding
uint8 is_bigendian
uint32 step
uint8[] data
)RB"},
    {R"RB(sensor_msgs/msg/Imu)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Quaternion orientation
float64[9] orientation_covariance
geometry_msgs/msg/Vector3 angular_velocity
float64[9] angular_velocity_covariance
geometry_msgs/msg/Vector3 linear_acceleration
float64[9] linear_acceleration_covariance
)RB"},
    {R"RB(sensor_msgs/msg/JointState)RB", R"RB(std_msgs/msg/Header header
string[] name
float64[] position
float64[] velocity
float64[] effort
)RB"},
    {R"RB(sensor_msgs/msg/Joy)RB", R"RB(std_msgs/msg/Header header
float32[] axes
int32[] buttons
)RB"},
    {R"RB(sensor_msgs/msg/JoyFeedback)RB", R"RB(uint8 TYPE_LED=0
uint8 TYPE_RUMBLE=1
uint8 TYPE_BUZZER=2
uint8 type
uint8 id
float32 intensity
)RB"},
    {R"RB(sensor_msgs/msg/JoyFeedbackArray)RB", R"RB(sensor_msgs/msg/JoyFeedback[] array
)RB"},
    {R"RB(sensor_msgs/msg/LaserEcho)RB", R"RB(float32[] echoes
)RB"},
    {R"RB(sensor_msgs/msg/LaserScan)RB", R"RB(std_msgs/msg/Header header
float32 angle_min
float32 angle_max
float32 angle_increment
float32 time_increment
float32 scan_time
float32 range_min
float32 range_max
float32[] ranges
float32[] intensities
)RB"},
    {R"RB(sensor_msgs/msg/MagneticField)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Vector3 magnetic_field
float64[9] magnetic_field_covariance
)RB"},
    {R"RB(sensor_msgs/msg/MultiDOFJointState)RB", R"RB(std_msgs/msg/Header header
string[] joint_names
geometry_msgs/msg/Transform[] transforms
geometry_msgs/msg/Twist[] twist
geometry_msgs/msg/Wrench[] wrench
)RB"},
    {R"RB(sensor_msgs/msg/MultiEchoLaserScan)RB", R"RB(std_msgs/msg/Header header
float32 angle_min
float32 angle_max
float32 angle_increment
float32 time_increment
float32 scan_time
float32 range_min
float32 range_max
sensor_msgs/msg/LaserEcho[] ranges
sensor_msgs/msg/LaserEcho[] intensities
)RB"},
    {R"RB(sensor_msgs/msg/NavSatFix)RB", R"RB(uint8 COVARIANCE_TYPE_UNKNOWN=0
uint8 COVARIANCE_TYPE_APPROXIMATED=1
uint8 COVARIANCE_TYPE_DIAGONAL_KNOWN=2
uint8 COVARIANCE_TYPE_KNOWN=3
std_msgs/msg/Header header
sensor_msgs/msg/NavSatStatus status
float64 latitude
float64 longitude
float64 altitude
float64[9] position_covariance
uint8 position_covariance_type
)RB"},
    {R"RB(sensor_msgs/msg/NavSatStatus)RB", R"RB(int8 STATUS_NO_FIX=-1
int8 STATUS_FIX=0
int8 STATUS_SBAS_FIX=1
int8 STATUS_GBAS_FIX=2
uint16 SERVICE_GPS=1
uint16 SERVICE_GLONASS=2
uint16 SERVICE_COMPASS=4
uint16 SERVICE_GALILEO=8
int8 status
uint16 service
)RB"},
    {R"RB(sensor_msgs/msg/PointCloud)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Point32[] points
sensor_msgs/msg/ChannelFloat32[] channels
)RB"},
    {R"RB(sensor_msgs/msg/PointCloud2)RB", R"RB(std_msgs/msg/Header header
uint32 height
uint32 width
sensor_msgs/msg/PointField[] fields
bool is_bigendian
uint32 point_step
uint32 row_step
uint8[] data
bool is_dense
)RB"},
    {R"RB(sensor_msgs/msg/PointField)RB", R"RB(uint8 INT8=1
uint8 UINT8=2
uint8 INT16=3
uint8 UINT16=4
uint8 INT32=5
uint8 UINT32=6
uint8 FLOAT32=7
uint8 FLOAT64=8
string name
uint32 offset
uint8 datatype
uint32 count
)RB"},
    {R"RB(sensor_msgs/msg/Range)RB", R"RB(uint8 ULTRASOUND=0
uint8 INFRARED=1
std_msgs/msg/Header header
uint8 radiation_type
float32 field_of_view
float32 min_range
float32 max_range
float32 range
)RB"},
    {R"RB(sensor_msgs/msg/RegionOfInterest)RB", R"RB(uint32 x_offset
uint32 y_offset
uint32 height
uint32 width
bool do_rectify
)RB"},
    {R"RB(sensor_msgs/msg/RelativeHumidity)RB", R"RB(std_msgs/msg/Header header
float64 relative_humidity
float64 variance
)RB"},
    {R"RB(sensor_msgs/msg/Temperature)RB", R"RB(std_msgs/msg/Header header
float64 temperature
float64 variance
)RB"},
    {R"RB(sensor_msgs/msg/TimeReference)RB", R"RB(std_msgs/msg/Header header
builtin_interfaces/msg/Time time_ref
string source
)RB"},
    {R"RB(shape_msgs/msg/Mesh)RB", R"RB(shape_msgs/msg/MeshTriangle[] triangles
geometry_msgs/msg/Point[] vertices
)RB"},
    {R"RB(shape_msgs/msg/MeshTriangle)RB", R"RB(uint32[3] vertex_indices
)RB"},
    {R"RB(shape_msgs/msg/Plane)RB", R"RB(float64[4] coef
)RB"},
    {R"RB(shape_msgs/msg/SolidPrimitive)RB", R"RB(uint8 BOX=1
uint8 SPHERE=2
uint8 CYLINDER=3
uint8 CONE=4
uint8 BOX_X=0
uint8 BOX_Y=1
uint8 BOX_Z=2
uint8 SPHERE_RADIUS=0
uint8 CYLINDER_HEIGHT=0
uint8 CYLINDER_RADIUS=1
uint8 CONE_HEIGHT=0
uint8 CONE_RADIUS=1
uint8 type
float64[<=3] dimensions
)RB"},
    {R"RB(std_msgs/msg/Bool)RB", R"RB(bool data
)RB"},
    {R"RB(std_msgs/msg/Byte)RB", R"RB(byte data
)RB"},
    {R"RB(std_msgs/msg/ByteMultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
byte[] data
)RB"},
    {R"RB(std_msgs/msg/Char)RB", R"RB(char data
)RB"},
    {R"RB(std_msgs/msg/ColorRGBA)RB", R"RB(float32 r
float32 g
float32 b
float32 a
)RB"},
    {R"RB(std_msgs/msg/Empty)RB", R"RB(uint8 structure_needs_at_least_one_member
)RB"},
    {R"RB(std_msgs/msg/Float32)RB", R"RB(float32 data
)RB"},
    {R"RB(std_msgs/msg/Float32MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
float32[] data
)RB"},
    {R"RB(std_msgs/msg/Float64)RB", R"RB(float64 data
)RB"},
    {R"RB(std_msgs/msg/Float64MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
float64[] data
)RB"},
    {R"RB(std_msgs/msg/Header)RB", R"RB(builtin_interfaces/msg/Time stamp
string frame_id
)RB"},
    {R"RB(std_msgs/msg/Int16)RB", R"RB(int16 data
)RB"},
    {R"RB(std_msgs/msg/Int16MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
int16[] data
)RB"},
    {R"RB(std_msgs/msg/Int32)RB", R"RB(int32 data
)RB"},
    {R"RB(std_msgs/msg/Int32MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
int32[] data
)RB"},
    {R"RB(std_msgs/msg/Int64)RB", R"RB(int64 data
)RB"},
    {R"RB(std_msgs/msg/Int64MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
int64[] data
)RB"},
    {R"RB(std_msgs/msg/Int8)RB", R"RB(int8 data
)RB"},
    {R"RB(std_msgs/msg/Int8MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
int8[] data
)RB"},
    {R"RB(std_msgs/msg/MultiArrayDimension)RB", R"RB(string label
uint32 size
uint32 stride
)RB"},
    {R"RB(std_msgs/msg/MultiArrayLayout)RB", R"RB(std_msgs/msg/MultiArrayDimension[] dim
uint32 data_offset
)RB"},
    {R"RB(std_msgs/msg/String)RB", R"RB(string data
)RB"},
    {R"RB(std_msgs/msg/UInt16)RB", R"RB(uint16 data
)RB"},
    {R"RB(std_msgs/msg/UInt16MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
uint16[] data
)RB"},
    {R"RB(std_msgs/msg/UInt32)RB", R"RB(uint32 data
)RB"},
    {R"RB(std_msgs/msg/UInt32MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
uint32[] data
)RB"},
    {R"RB(std_msgs/msg/UInt64)RB", R"RB(uint64 data
)RB"},
    {R"RB(std_msgs/msg/UInt64MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
uint64[] data
)RB"},
    {R"RB(std_msgs/msg/UInt8)RB", R"RB(uint8 data
)RB"},
    {R"RB(std_msgs/msg/UInt8MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
uint8[] data
)RB"},
    {R"RB(stereo_msgs/msg/DisparityImage)RB", R"RB(std_msgs/msg/Header header
sensor_msgs/msg/Image image
float32 f
float32 t
sensor_msgs/msg/RegionOfInterest valid_window
float32 min_disparity
float32 max_disparity
float32 delta_d
)RB"},
    {R"RB(tf2_msgs/msg/TF2Error)RB", R"RB(uint8 NO_ERROR=0
uint8 LOOKUP_ERROR=1
uint8 CONNECTIVITY_ERROR=2
uint8 EXTRAPOLATION_ERROR=3
uint8 INVALID_ARGUMENT_ERROR=4
uint8 TIMEOUT_ERROR=5
uint8 TRANSFORM_ERROR=6
uint8 error
string error_string
)RB"},
    {R"RB(tf2_msgs/msg/TFMessage)RB", R"RB(geometry_msgs/msg/TransformStamped[] transforms
)RB"},
    {R"RB(trajectory_msgs/msg/JointTrajectory)RB", R"RB(std_msgs/msg/Header header
string[] joint_names
trajectory_msgs/msg/JointTrajectoryPoint[] points
)RB"},
    {R"RB(trajectory_msgs/msg/JointTrajectoryPoint)RB", R"RB(float64[] positions
float64[] velocities
float64[] accelerations
float64[] effort
builtin_interfaces/msg/Duration time_from_start
)RB"},
    {R"RB(trajectory_msgs/msg/MultiDOFJointTrajectory)RB", R"RB(std_msgs/msg/Header header
string[] joint_names
trajectory_msgs/msg/MultiDOFJointTrajectoryPoint[] points
)RB"},
    {R"RB(trajectory_msgs/msg/MultiDOFJointTrajectoryPoint)RB", R"RB(geometry_msgs/msg/Transform[] transforms
geometry_msgs/msg/Twist[] velocities
geometry_msgs/msg/Twist[] accelerations
builtin_interfaces/msg/Duration time_from_start
)RB"},
    {R"RB(unique_identifier_msgs/msg/UUID)RB", R"RB(uint8[16] uuid
)RB"},
    {R"RB(visualization_msgs/msg/ImageMarker)RB", R"RB(uint8 CIRCLE=0
uint8 LINE_STRIP=1
uint8 LINE_LIST=2
uint8 POLYGON=3
uint8 POINTS=4
uint8 ADD=0
uint8 REMOVE=1
std_msgs/msg/Header header
string ns
int32 id
int32 type
int32 action
geometry_msgs/msg/Point position
float32 scale
std_msgs/msg/ColorRGBA outline_color
uint8 filled
std_msgs/msg/ColorRGBA fill_color
builtin_interfaces/msg/Duration lifetime
geometry_msgs/msg/Point[] points
std_msgs/msg/ColorRGBA[] outline_colors
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarker)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Pose pose
string name
string description
float32 scale
visualization_msgs/msg/MenuEntry[] menu_entries
visualization_msgs/msg/InteractiveMarkerControl[] controls
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerControl)RB", R"RB(uint8 INHERIT=0
uint8 FIXED=1
uint8 VIEW_FACING=2
uint8 NONE=0
uint8 MENU=1
uint8 BUTTON=2
uint8 MOVE_AXIS=3
uint8 MOVE_PLANE=4
uint8 ROTATE_AXIS=5
uint8 MOVE_ROTATE=6
uint8 MOVE_3D=7
uint8 ROTATE_3D=8
uint8 MOVE_ROTATE_3D=9
string name
geometry_msgs/msg/Quaternion orientation
uint8 orientation_mode
uint8 interaction_mode
bool always_visible
visualization_msgs/msg/Marker[] markers
bool independent_marker_orientation
string description
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerFeedback)RB", R"RB(uint8 KEEP_ALIVE=0
uint8 POSE_UPDATE=1
uint8 MENU_SELECT=2
uint8 BUTTON_CLICK=3
uint8 MOUSE_DOWN=4
uint8 MOUSE_UP=5
std_msgs/msg/Header header
string client_id
string marker_name
string control_name
uint8 event_type
geometry_msgs/msg/Pose pose
uint32 menu_entry_id
geometry_msgs/msg/Point mouse_point
bool mouse_point_valid
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerInit)RB", R"RB(string server_id
uint64 seq_num
visualization_msgs/msg/InteractiveMarker[] markers
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerPose)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Pose pose
string name
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerUpdate)RB", R"RB(uint8 KEEP_ALIVE=0
uint8 UPDATE=1
string server_id
uint64 seq_num
uint8 type
visualization_msgs/msg/InteractiveMarker[] markers
visualization_msgs/msg/InteractiveMarkerPose[] poses
string[] erases
)RB"},
    {R"RB(visualization_msgs/msg/Marker)RB", R"RB(uint8 ARROW=0
uint8 CUBE=1
uint8 SPHERE=2
uint8 CYLINDER=3
uint8 LINE_STRIP=4
uint8 LINE_LIST=5
uint8 CUBE_LIST=6
uint8 SPHERE_LIST=7
uint8 POINTS=8
uint8 TEXT_VIEW_FACING=9
uint8 MESH_RESOURCE=10
uint8 TRIANGLE_LIST=11
uint8 ADD=0
uint8 MODIFY=0
uint8 DELETE=2
uint8 DELETEALL=3
std_msgs/msg/Header header
string ns
int32 id
int32 type
int32 action
geometry_msgs/msg/Pose pose
geometry_msgs/msg/Vector3 scale
std_msgs/msg/ColorRGBA color
builtin_interfaces/msg/Duration lifetime
bool frame_locked
geometry_msgs/msg/Point[] points
std_msgs/msg/ColorRGBA[] colors
string text
string mesh_resource
bool mesh_use_embedded_materials
)RB"},
    {R"RB(visualization_msgs/msg/MarkerArray)RB", R"RB(visualization_msgs/msg/Marker[] markers
)RB"},
    {R"RB(visualization_msgs/msg/MenuEntry)RB", R"RB(uint8 FEEDBACK=0
uint8 ROSRUN=1
uint8 ROSLAUNCH=2
uint32 id
uint32 parent_id
string title
string command
uint8 command_type
)RB"},
};

const GeneratedTypeDefinition kRos2FoxyTypes[] = {
    {R"RB(action_msgs/msg/GoalInfo)RB", R"RB(unique_identifier_msgs/msg/UUID goal_id
builtin_interfaces/msg/Time stamp
)RB"},
    {R"RB(action_msgs/msg/GoalStatus)RB", R"RB(int8 STATUS_UNKNOWN=0
int8 STATUS_ACCEPTED=1
int8 STATUS_EXECUTING=2
int8 STATUS_CANCELING=3
int8 STATUS_SUCCEEDED=4
int8 STATUS_CANCELED=5
int8 STATUS_ABORTED=6
action_msgs/msg/GoalInfo goal_info
int8 status
)RB"},
    {R"RB(action_msgs/msg/GoalStatusArray)RB", R"RB(action_msgs/msg/GoalStatus[] status_list
)RB"},
    {R"RB(actionlib_msgs/msg/GoalID)RB", R"RB(builtin_interfaces/msg/Time stamp
string id
)RB"},
    {R"RB(actionlib_msgs/msg/GoalStatus)RB", R"RB(uint8 PENDING=0
uint8 ACTIVE=1
uint8 PREEMPTED=2
uint8 SUCCEEDED=3
uint8 ABORTED=4
uint8 REJECTED=5
uint8 PREEMPTING=6
uint8 RECALLING=7
uint8 RECALLED=8
uint8 LOST=9
actionlib_msgs/msg/GoalID goal_id
uint8 status
string text
)RB"},
    {R"RB(actionlib_msgs/msg/GoalStatusArray)RB", R"RB(std_msgs/msg/Header header
actionlib_msgs/msg/GoalStatus[] status_list
)RB"},
    {R"RB(builtin_interfaces/msg/Duration)RB", R"RB(int32 sec
uint32 nanosec
)RB"},
    {R"RB(builtin_interfaces/msg/Time)RB", R"RB(int32 sec
uint32 nanosec
)RB"},
    {R"RB(diagnostic_msgs/msg/DiagnosticArray)RB", R"RB(std_msgs/msg/Header header
diagnostic_msgs/msg/DiagnosticStatus[] status
)RB"},
    {R"RB(diagnostic_msgs/msg/DiagnosticStatus)RB", R"RB(byte OK=0
byte WARN=1
byte ERROR=2
byte STALE=3
byte level
string name
string message
string hardware_id
diagnostic_msgs/msg/KeyValue[] values
)RB"},
    {R"RB(diagnostic_msgs/msg/KeyValue)RB", R"RB(string key
string value
)RB"},
    {R"RB(geometry_msgs/msg/Accel)RB", R"RB(geometry_msgs/msg/Vector3 linear
geometry_msgs/msg/Vector3 angular
)RB"},
    {R"RB(geometry_msgs/msg/AccelStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Accel accel
)RB"},
    {R"RB(geometry_msgs/msg/AccelWithCovariance)RB", R"RB(geometry_msgs/msg/Accel accel
float64[36] covariance
)RB"},
    {R"RB(geometry_msgs/msg/AccelWithCovarianceStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/AccelWithCovariance accel
)RB"},
    {R"RB(geometry_msgs/msg/Inertia)RB", R"RB(float64 m
geometry_msgs/msg/Vector3 com
float64 ixx
float64 ixy
float64 ixz
float64 iyy
float64 iyz
float64 izz
)RB"},
    {R"RB(geometry_msgs/msg/InertiaStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Inertia inertia
)RB"},
    {R"RB(geometry_msgs/msg/Point)RB", R"RB(float64 x
float64 y
float64 z
)RB"},
    {R"RB(geometry_msgs/msg/Point32)RB", R"RB(float32 x
float32 y
float32 z
)RB"},
    {R"RB(geometry_msgs/msg/PointStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Point point
)RB"},
    {R"RB(geometry_msgs/msg/Polygon)RB", R"RB(geometry_msgs/msg/Point32[] points
)RB"},
    {R"RB(geometry_msgs/msg/PolygonStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Polygon polygon
)RB"},
    {R"RB(geometry_msgs/msg/Pose)RB", R"RB(geometry_msgs/msg/Point position
geometry_msgs/msg/Quaternion orientation
)RB"},
    {R"RB(geometry_msgs/msg/Pose2D)RB", R"RB(float64 x
float64 y
float64 theta
)RB"},
    {R"RB(geometry_msgs/msg/PoseArray)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Pose[] poses
)RB"},
    {R"RB(geometry_msgs/msg/PoseStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Pose pose
)RB"},
    {R"RB(geometry_msgs/msg/PoseWithCovariance)RB", R"RB(geometry_msgs/msg/Pose pose
float64[36] covariance
)RB"},
    {R"RB(geometry_msgs/msg/PoseWithCovarianceStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/PoseWithCovariance pose
)RB"},
    {R"RB(geometry_msgs/msg/Quaternion)RB", R"RB(float64 x
float64 y
float64 z
float64 w
)RB"},
    {R"RB(geometry_msgs/msg/QuaternionStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Quaternion quaternion
)RB"},
    {R"RB(geometry_msgs/msg/Transform)RB", R"RB(geometry_msgs/msg/Vector3 translation
geometry_msgs/msg/Quaternion rotation
)RB"},
    {R"RB(geometry_msgs/msg/TransformStamped)RB", R"RB(std_msgs/msg/Header header
string child_frame_id
geometry_msgs/msg/Transform transform
)RB"},
    {R"RB(geometry_msgs/msg/Twist)RB", R"RB(geometry_msgs/msg/Vector3 linear
geometry_msgs/msg/Vector3 angular
)RB"},
    {R"RB(geometry_msgs/msg/TwistStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Twist twist
)RB"},
    {R"RB(geometry_msgs/msg/TwistWithCovariance)RB", R"RB(geometry_msgs/msg/Twist twist
float64[36] covariance
)RB"},
    {R"RB(geometry_msgs/msg/TwistWithCovarianceStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/TwistWithCovariance twist
)RB"},
    {R"RB(geometry_msgs/msg/Vector3)RB", R"RB(float64 x
float64 y
float64 z
)RB"},
    {R"RB(geometry_msgs/msg/Vector3Stamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Vector3 vector
)RB"},
    {R"RB(geometry_msgs/msg/Wrench)RB", R"RB(geometry_msgs/msg/Vector3 force
geometry_msgs/msg/Vector3 torque
)RB"},
    {R"RB(geometry_msgs/msg/WrenchStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Wrench wrench
)RB"},
    {R"RB(libstatistics_collector/msg/DummyMessage)RB", R"RB(std_msgs/msg/Header header
)RB"},
    {R"RB(lifecycle_msgs/msg/State)RB", R"RB(uint8 PRIMARY_STATE_UNKNOWN=0
uint8 PRIMARY_STATE_UNCONFIGURED=1
uint8 PRIMARY_STATE_INACTIVE=2
uint8 PRIMARY_STATE_ACTIVE=3
uint8 PRIMARY_STATE_FINALIZED=4
uint8 TRANSITION_STATE_CONFIGURING=10
uint8 TRANSITION_STATE_CLEANINGUP=11
uint8 TRANSITION_STATE_SHUTTINGDOWN=12
uint8 TRANSITION_STATE_ACTIVATING=13
uint8 TRANSITION_STATE_DEACTIVATING=14
uint8 TRANSITION_STATE_ERRORPROCESSING=15
uint8 id
string label
)RB"},
    {R"RB(lifecycle_msgs/msg/Transition)RB", R"RB(uint8 TRANSITION_CREATE=0
uint8 TRANSITION_CONFIGURE=1
uint8 TRANSITION_CLEANUP=2
uint8 TRANSITION_ACTIVATE=3
uint8 TRANSITION_DEACTIVATE=4
uint8 TRANSITION_UNCONFIGURED_SHUTDOWN=5
uint8 TRANSITION_INACTIVE_SHUTDOWN=6
uint8 TRANSITION_ACTIVE_SHUTDOWN=7
uint8 TRANSITION_DESTROY=8
uint8 TRANSITION_ON_CONFIGURE_SUCCESS=10
uint8 TRANSITION_ON_CONFIGURE_FAILURE=11
uint8 TRANSITION_ON_CONFIGURE_ERROR=12
uint8 TRANSITION_ON_CLEANUP_SUCCESS=20
uint8 TRANSITION_ON_CLEANUP_FAILURE=21
uint8 TRANSITION_ON_CLEANUP_ERROR=22
uint8 TRANSITION_ON_ACTIVATE_SUCCESS=30
uint8 TRANSITION_ON_ACTIVATE_FAILURE=31
uint8 TRANSITION_ON_ACTIVATE_ERROR=32
uint8 TRANSITION_ON_DEACTIVATE_SUCCESS=40
uint8 TRANSITION_ON_DEACTIVATE_FAILURE=41
uint8 TRANSITION_ON_DEACTIVATE_ERROR=42
uint8 TRANSITION_ON_SHUTDOWN_SUCCESS=50
uint8 TRANSITION_ON_SHUTDOWN_FAILURE=51
uint8 TRANSITION_ON_SHUTDOWN_ERROR=52
uint8 TRANSITION_ON_ERROR_SUCCESS=60
uint8 TRANSITION_ON_ERROR_FAILURE=61
uint8 TRANSITION_ON_ERROR_ERROR=62
uint8 TRANSITION_CALLBACK_SUCCESS=97
uint8 TRANSITION_CALLBACK_FAILURE=98
uint8 TRANSITION_CALLBACK_ERROR=99
uint8 id
string label
)RB"},
    {R"RB(lifecycle_msgs/msg/TransitionDescription)RB", R"RB(lifecycle_msgs/msg/Transition transition
lifecycle_msgs/msg/State start_state
lifecycle_msgs/msg/State goal_state
)RB"},
    {R"RB(lifecycle_msgs/msg/TransitionEvent)RB", R"RB(uint64 timestamp
lifecycle_msgs/msg/Transition transition
lifecycle_msgs/msg/State start_state
lifecycle_msgs/msg/State goal_state
)RB"},
    {R"RB(nav_msgs/msg/GridCells)RB", R"RB(std_msgs/msg/Header header
float32 cell_width
float32 cell_height
geometry_msgs/msg/Point[] cells
)RB"},
    {R"RB(nav_msgs/msg/MapMetaData)RB", R"RB(builtin_interfaces/msg/Time map_load_time
float32 resolution
uint32 width
uint32 height
geometry_msgs/msg/Pose origin
)RB"},
    {R"RB(nav_msgs/msg/OccupancyGrid)RB", R"RB(std_msgs/msg/Header header
nav_msgs/msg/MapMetaData info
int8[] data
)RB"},
    {R"RB(nav_msgs/msg/Odometry)RB", R"RB(std_msgs/msg/Header header
string child_frame_id
geometry_msgs/msg/PoseWithCovariance pose
geometry_msgs/msg/TwistWithCovariance twist
)RB"},
    {R"RB(nav_msgs/msg/Path)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/PoseStamped[] poses
)RB"},
    {R"RB(rcl_interfaces/msg/FloatingPointRange)RB", R"RB(float64 from_value
float64 to_value
float64 step
)RB"},
    {R"RB(rcl_interfaces/msg/IntegerRange)RB", R"RB(int64 from_value
int64 to_value
uint64 step
)RB"},
    {R"RB(rcl_interfaces/msg/ListParametersResult)RB", R"RB(string[] names
string[] prefixes
)RB"},
    {R"RB(rcl_interfaces/msg/Log)RB", R"RB(byte DEBUG=10
byte INFO=20
byte WARN=30
byte ERROR=40
byte FATAL=50
builtin_interfaces/msg/Time stamp
uint8 level
string name
string msg
string file
string function
uint32 line
)RB"},
    {R"RB(rcl_interfaces/msg/Parameter)RB", R"RB(string name
rcl_interfaces/msg/ParameterValue value
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterDescriptor)RB", R"RB(string name
uint8 type
string description
string additional_constraints
bool read_only
rcl_interfaces/msg/FloatingPointRange[<=1] floating_point_range
rcl_interfaces/msg/IntegerRange[<=1] integer_range
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterEvent)RB", R"RB(builtin_interfaces/msg/Time stamp
string node
rcl_interfaces/msg/Parameter[] new_parameters
rcl_interfaces/msg/Parameter[] changed_parameters
rcl_interfaces/msg/Parameter[] deleted_parameters
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterEventDescriptors)RB", R"RB(rcl_interfaces/msg/ParameterDescriptor[] new_parameters
rcl_interfaces/msg/ParameterDescriptor[] changed_parameters
rcl_interfaces/msg/ParameterDescriptor[] deleted_parameters
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterType)RB", R"RB(uint8 PARAMETER_NOT_SET=0
uint8 PARAMETER_BOOL=1
uint8 PARAMETER_INTEGER=2
uint8 PARAMETER_DOUBLE=3
uint8 PARAMETER_STRING=4
uint8 PARAMETER_BYTE_ARRAY=5
uint8 PARAMETER_BOOL_ARRAY=6
uint8 PARAMETER_INTEGER_ARRAY=7
uint8 PARAMETER_DOUBLE_ARRAY=8
uint8 PARAMETER_STRING_ARRAY=9
uint8 structure_needs_at_least_one_member
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterValue)RB", R"RB(uint8 type
bool bool_value
int64 integer_value
float64 double_value
string string_value
byte[] byte_array_value
bool[] bool_array_value
int64[] integer_array_value
float64[] double_array_value
string[] string_array_value
)RB"},
    {R"RB(rcl_interfaces/msg/SetParametersResult)RB", R"RB(bool successful
string reason
)RB"},
    {R"RB(rmw_dds_common/msg/Gid)RB", R"RB(char[24] data
)RB"},
    {R"RB(rmw_dds_common/msg/NodeEntitiesInfo)RB", R"RB(string<=256 node_namespace
string<=256 node_name
rmw_dds_common/msg/Gid[] reader_gid_seq
rmw_dds_common/msg/Gid[] writer_gid_seq
)RB"},
    {R"RB(rmw_dds_common/msg/ParticipantEntitiesInfo)RB", R"RB(rmw_dds_common/msg/Gid gid
rmw_dds_common/msg/NodeEntitiesInfo[] node_entities_info_seq
)RB"},
    {R"RB(rosgraph_msgs/msg/Clock)RB", R"RB(builtin_interfaces/msg/Time clock
)RB"},
    {R"RB(sensor_msgs/msg/BatteryState)RB", R"RB(uint8 POWER_SUPPLY_STATUS_UNKNOWN=0
uint8 POWER_SUPPLY_STATUS_CHARGING=1
uint8 POWER_SUPPLY_STATUS_DISCHARGING=2
uint8 POWER_SUPPLY_STATUS_NOT_CHARGING=3
uint8 POWER_SUPPLY_STATUS_FULL=4
uint8 POWER_SUPPLY_HEALTH_UNKNOWN=0
uint8 POWER_SUPPLY_HEALTH_GOOD=1
uint8 POWER_SUPPLY_HEALTH_OVERHEAT=2
uint8 POWER_SUPPLY_HEALTH_DEAD=3
uint8 POWER_SUPPLY_HEALTH_OVERVOLTAGE=4
uint8 POWER_SUPPLY_HEALTH_UNSPEC_FAILURE=5
uint8 POWER_SUPPLY_HEALTH_COLD=6
uint8 POWER_SUPPLY_HEALTH_WATCHDOG_TIMER_EXPIRE=7
uint8 POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE=8
uint8 POWER_SUPPLY_TECHNOLOGY_UNKNOWN=0
uint8 POWER_SUPPLY_TECHNOLOGY_NIMH=1
uint8 POWER_SUPPLY_TECHNOLOGY_LION=2
uint8 POWER_SUPPLY_TECHNOLOGY_LIPO=3
uint8 POWER_SUPPLY_TECHNOLOGY_LIFE=4
uint8 POWER_SUPPLY_TECHNOLOGY_NICD=5
uint8 POWER_SUPPLY_TECHNOLOGY_LIMN=6
std_msgs/msg/Header header
float32 voltage
float32 temperature
float32 current
float32 charge
float32 capacity
float32 design_capacity
float32 percentage
uint8 power_supply_status
uint8 power_supply_health
uint8 power_supply_technology
bool present
float32[] cell_voltage
float32[] cell_temperature
string location
string serial_number
)RB"},
    {R"RB(sensor_msgs/msg/CameraInfo)RB", R"RB(std_msgs/msg/Header header
uint32 height
uint32 width
string distortion_model
float64[] d
float64[9] k
float64[9] r
float64[12] p
uint32 binning_x
uint32 binning_y
sensor_msgs/msg/RegionOfInterest roi
)RB"},
    {R"RB(sensor_msgs/msg/ChannelFloat32)RB", R"RB(string name
float32[] values
)RB"},
    {R"RB(sensor_msgs/msg/CompressedImage)RB", R"RB(std_msgs/msg/Header header
string format
uint8[] data
)RB"},
    {R"RB(sensor_msgs/msg/FluidPressure)RB", R"RB(std_msgs/msg/Header header
float64 fluid_pressure
float64 variance
)RB"},
    {R"RB(sensor_msgs/msg/Illuminance)RB", R"RB(std_msgs/msg/Header header
float64 illuminance
float64 variance
)RB"},
    {R"RB(sensor_msgs/msg/Image)RB", R"RB(std_msgs/msg/Header header
uint32 height
uint32 width
string encoding
uint8 is_bigendian
uint32 step
uint8[] data
)RB"},
    {R"RB(sensor_msgs/msg/Imu)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Quaternion orientation
float64[9] orientation_covariance
geometry_msgs/msg/Vector3 angular_velocity
float64[9] angular_velocity_covariance
geometry_msgs/msg/Vector3 linear_acceleration
float64[9] linear_acceleration_covariance
)RB"},
    {R"RB(sensor_msgs/msg/JointState)RB", R"RB(std_msgs/msg/Header header
string[] name
float64[] position
float64[] velocity
float64[] effort
)RB"},
    {R"RB(sensor_msgs/msg/Joy)RB", R"RB(std_msgs/msg/Header header
float32[] axes
int32[] buttons
)RB"},
    {R"RB(sensor_msgs/msg/JoyFeedback)RB", R"RB(uint8 TYPE_LED=0
uint8 TYPE_RUMBLE=1
uint8 TYPE_BUZZER=2
uint8 type
uint8 id
float32 intensity
)RB"},
    {R"RB(sensor_msgs/msg/JoyFeedbackArray)RB", R"RB(sensor_msgs/msg/JoyFeedback[] array
)RB"},
    {R"RB(sensor_msgs/msg/LaserEcho)RB", R"RB(float32[] echoes
)RB"},
    {R"RB(sensor_msgs/msg/LaserScan)RB", R"RB(std_msgs/msg/Header header
float32 angle_min
float32 angle_max
float32 angle_increment
float32 time_increment
float32 scan_time
float32 range_min
float32 range_max
float32[] ranges
float32[] intensities
)RB"},
    {R"RB(sensor_msgs/msg/MagneticField)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Vector3 magnetic_field
float64[9] magnetic_field_covariance
)RB"},
    {R"RB(sensor_msgs/msg/MultiDOFJointState)RB", R"RB(std_msgs/msg/Header header
string[] joint_names
geometry_msgs/msg/Transform[] transforms
geometry_msgs/msg/Twist[] twist
geometry_msgs/msg/Wrench[] wrench
)RB"},
    {R"RB(sensor_msgs/msg/MultiEchoLaserScan)RB", R"RB(std_msgs/msg/Header header
float32 angle_min
float32 angle_max
float32 angle_increment
float32 time_increment
float32 scan_time
float32 range_min
float32 range_max
sensor_msgs/msg/LaserEcho[] ranges
sensor_msgs/msg/LaserEcho[] intensities
)RB"},
    {R"RB(sensor_msgs/msg/NavSatFix)RB", R"RB(uint8 COVARIANCE_TYPE_UNKNOWN=0
uint8 COVARIANCE_TYPE_APPROXIMATED=1
uint8 COVARIANCE_TYPE_DIAGONAL_KNOWN=2
uint8 COVARIANCE_TYPE_KNOWN=3
std_msgs/msg/Header header
sensor_msgs/msg/NavSatStatus status
float64 latitude
float64 longitude
float64 altitude
float64[9] position_covariance
uint8 position_covariance_type
)RB"},
    {R"RB(sensor_msgs/msg/NavSatStatus)RB", R"RB(int8 STATUS_NO_FIX=-1
int8 STATUS_FIX=0
int8 STATUS_SBAS_FIX=1
int8 STATUS_GBAS_FIX=2
uint16 SERVICE_GPS=1
uint16 SERVICE_GLONASS=2
uint16 SERVICE_COMPASS=4
uint16 SERVICE_GALILEO=8
int8 status
uint16 service
)RB"},
    {R"RB(sensor_msgs/msg/PointCloud)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Point32[] points
sensor_msgs/msg/ChannelFloat32[] channels
)RB"},
    {R"RB(sensor_msgs/msg/PointCloud2)RB", R"RB(std_msgs/msg/Header header
uint32 height
uint32 width
sensor_msgs/msg/PointField[] fields
bool is_bigendian
uint32 point_step
uint32 row_step
uint8[] data
bool is_dense
)RB"},
    {R"RB(sensor_msgs/msg/PointField)RB", R"RB(uint8 INT8=1
uint8 UINT8=2
uint8 INT16=3
uint8 UINT16=4
uint8 INT32=5
uint8 UINT32=6
uint8 FLOAT32=7
uint8 FLOAT64=8
string name
uint32 offset
uint8 datatype
uint32 count
)RB"},
    {R"RB(sensor_msgs/msg/Range)RB", R"RB(uint8 ULTRASOUND=0
uint8 INFRARED=1
std_msgs/msg/Header header
uint8 radiation_type
float32 field_of_view
float32 min_range
float32 max_range
float32 range
)RB"},
    {R"RB(sensor_msgs/msg/RegionOfInterest)RB", R"RB(uint32 x_offset
uint32 y_offset
uint32 height
uint32 width
bool do_rectify
)RB"},
    {R"RB(sensor_msgs/msg/RelativeHumidity)RB", R"RB(std_msgs/msg/Header header
float64 relative_humidity
float64 variance
)RB"},
    {R"RB(sensor_msgs/msg/Temperature)RB", R"RB(std_msgs/msg/Header header
float64 temperature
float64 variance
)RB"},
    {R"RB(sensor_msgs/msg/TimeReference)RB", R"RB(std_msgs/msg/Header header
builtin_interfaces/msg/Time time_ref
string source
)RB"},
    {R"RB(shape_msgs/msg/Mesh)RB", R"RB(shape_msgs/msg/MeshTriangle[] triangles
geometry_msgs/msg/Point[] vertices
)RB"},
    {R"RB(shape_msgs/msg/MeshTriangle)RB", R"RB(uint32[3] vertex_indices
)RB"},
    {R"RB(shape_msgs/msg/Plane)RB", R"RB(float64[4] coef
)RB"},
    {R"RB(shape_msgs/msg/SolidPrimitive)RB", R"RB(uint8 BOX=1
uint8 SPHERE=2
uint8 CYLINDER=3
uint8 CONE=4
uint8 BOX_X=0
uint8 BOX_Y=1
uint8 BOX_Z=2
uint8 SPHERE_RADIUS=0
uint8 CYLINDER_HEIGHT=0
uint8 CYLINDER_RADIUS=1
uint8 CONE_HEIGHT=0
uint8 CONE_RADIUS=1
uint8 type
float64[<=3] dimensions
)RB"},
    {R"RB(statistics_msgs/msg/MetricsMessage)RB", R"RB(string measurement_source_name
string metrics_source
string unit
builtin_interfaces/msg/Time window_start
builtin_interfaces/msg/Time window_stop
statistics_msgs/msg/StatisticDataPoint[] statistics
)RB"},
    {R"RB(statistics_msgs/msg/StatisticDataPoint)RB", R"RB(uint8 data_type
float64 data
)RB"},
    {R"RB(statistics_msgs/msg/StatisticDataType)RB", R"RB(uint8 STATISTICS_DATA_TYPE_UNINITIALIZED=0
uint8 STATISTICS_DATA_TYPE_AVERAGE=1
uint8 STATISTICS_DATA_TYPE_MINIMUM=2
uint8 STATISTICS_DATA_TYPE_MAXIMUM=3
uint8 STATISTICS_DATA_TYPE_STDDEV=4
uint8 STATISTICS_DATA_TYPE_SAMPLE_COUNT=5
uint8 structure_needs_at_least_one_member
)RB"},
    {R"RB(std_msgs/msg/Bool)RB", R"RB(bool data
)RB"},
    {R"RB(std_msgs/msg/Byte)RB", R"RB(byte data
)RB"},
    {R"RB(std_msgs/msg/ByteMultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
byte[] data
)RB"},
    {R"RB(std_msgs/msg/Char)RB", R"RB(char data
)RB"},
    {R"RB(std_msgs/msg/ColorRGBA)RB", R"RB(float32 r
float32 g
float32 b
float32 a
)RB"},
    {R"RB(std_msgs/msg/Empty)RB", R"RB(uint8 structure_needs_at_least_one_member
)RB"},
    {R"RB(std_msgs/msg/Float32)RB", R"RB(float32 data
)RB"},
    {R"RB(std_msgs/msg/Float32MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
float32[] data
)RB"},
    {R"RB(std_msgs/msg/Float64)RB", R"RB(float64 data
)RB"},
    {R"RB(std_msgs/msg/Float64MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
float64[] data
)RB"},
    {R"RB(std_msgs/msg/Header)RB", R"RB(builtin_interfaces/msg/Time stamp
string frame_id
)RB"},
    {R"RB(std_msgs/msg/Int16)RB", R"RB(int16 data
)RB"},
    {R"RB(std_msgs/msg/Int16MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
int16[] data
)RB"},
    {R"RB(std_msgs/msg/Int32)RB", R"RB(int32 data
)RB"},
    {R"RB(std_msgs/msg/Int32MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
int32[] data
)RB"},
    {R"RB(std_msgs/msg/Int64)RB", R"RB(int64 data
)RB"},
    {R"RB(std_msgs/msg/Int64MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
int64[] data
)RB"},
    {R"RB(std_msgs/msg/Int8)RB", R"RB(int8 data
)RB"},
    {R"RB(std_msgs/msg/Int8MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
int8[] data
)RB"},
    {R"RB(std_msgs/msg/MultiArrayDimension)RB", R"RB(string label
uint32 size
uint32 stride
)RB"},
    {R"RB(std_msgs/msg/MultiArrayLayout)RB", R"RB(std_msgs/msg/MultiArrayDimension[] dim
uint32 data_offset
)RB"},
    {R"RB(std_msgs/msg/String)RB", R"RB(string data
)RB"},
    {R"RB(std_msgs/msg/UInt16)RB", R"RB(uint16 data
)RB"},
    {R"RB(std_msgs/msg/UInt16MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
uint16[] data
)RB"},
    {R"RB(std_msgs/msg/UInt32)RB", R"RB(uint32 data
)RB"},
    {R"RB(std_msgs/msg/UInt32MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
uint32[] data
)RB"},
    {R"RB(std_msgs/msg/UInt64)RB", R"RB(uint64 data
)RB"},
    {R"RB(std_msgs/msg/UInt64MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
uint64[] data
)RB"},
    {R"RB(std_msgs/msg/UInt8)RB", R"RB(uint8 data
)RB"},
    {R"RB(std_msgs/msg/UInt8MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
uint8[] data
)RB"},
    {R"RB(stereo_msgs/msg/DisparityImage)RB", R"RB(std_msgs/msg/Header header
sensor_msgs/msg/Image image
float32 f
float32 t
sensor_msgs/msg/RegionOfInterest valid_window
float32 min_disparity
float32 max_disparity
float32 delta_d
)RB"},
    {R"RB(tf2_msgs/msg/TF2Error)RB", R"RB(uint8 NO_ERROR=0
uint8 LOOKUP_ERROR=1
uint8 CONNECTIVITY_ERROR=2
uint8 EXTRAPOLATION_ERROR=3
uint8 INVALID_ARGUMENT_ERROR=4
uint8 TIMEOUT_ERROR=5
uint8 TRANSFORM_ERROR=6
uint8 error
string error_string
)RB"},
    {R"RB(tf2_msgs/msg/TFMessage)RB", R"RB(geometry_msgs/msg/TransformStamped[] transforms
)RB"},
    {R"RB(trajectory_msgs/msg/JointTrajectory)RB", R"RB(std_msgs/msg/Header header
string[] joint_names
trajectory_msgs/msg/JointTrajectoryPoint[] points
)RB"},
    {R"RB(trajectory_msgs/msg/JointTrajectoryPoint)RB", R"RB(float64[] positions
float64[] velocities
float64[] accelerations
float64[] effort
builtin_interfaces/msg/Duration time_from_start
)RB"},
    {R"RB(trajectory_msgs/msg/MultiDOFJointTrajectory)RB", R"RB(std_msgs/msg/Header header
string[] joint_names
trajectory_msgs/msg/MultiDOFJointTrajectoryPoint[] points
)RB"},
    {R"RB(trajectory_msgs/msg/MultiDOFJointTrajectoryPoint)RB", R"RB(geometry_msgs/msg/Transform[] transforms
geometry_msgs/msg/Twist[] velocities
geometry_msgs/msg/Twist[] accelerations
builtin_interfaces/msg/Duration time_from_start
)RB"},
    {R"RB(unique_identifier_msgs/msg/UUID)RB", R"RB(uint8[16] uuid
)RB"},
    {R"RB(visualization_msgs/msg/ImageMarker)RB", R"RB(int32 CIRCLE=0
int32 LINE_STRIP=1
int32 LINE_LIST=2
int32 POLYGON=3
int32 POINTS=4
int32 ADD=0
int32 REMOVE=1
std_msgs/msg/Header header
string ns
int32 id
int32 type
int32 action
geometry_msgs/msg/Point position
float32 scale
std_msgs/msg/ColorRGBA outline_color
uint8 filled
std_msgs/msg/ColorRGBA fill_color
builtin_interfaces/msg/Duration lifetime
geometry_msgs/msg/Point[] points
std_msgs/msg/ColorRGBA[] outline_colors
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarker)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Pose pose
string name
string description
float32 scale
visualization_msgs/msg/MenuEntry[] menu_entries
visualization_msgs/msg/InteractiveMarkerControl[] controls
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerControl)RB", R"RB(uint8 INHERIT=0
uint8 FIXED=1
uint8 VIEW_FACING=2
uint8 NONE=0
uint8 MENU=1
uint8 BUTTON=2
uint8 MOVE_AXIS=3
uint8 MOVE_PLANE=4
uint8 ROTATE_AXIS=5
uint8 MOVE_ROTATE=6
uint8 MOVE_3D=7
uint8 ROTATE_3D=8
uint8 MOVE_ROTATE_3D=9
string name
geometry_msgs/msg/Quaternion orientation
uint8 orientation_mode
uint8 interaction_mode
bool always_visible
visualization_msgs/msg/Marker[] markers
bool independent_marker_orientation
string description
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerFeedback)RB", R"RB(uint8 KEEP_ALIVE=0
uint8 POSE_UPDATE=1
uint8 MENU_SELECT=2
uint8 BUTTON_CLICK=3
uint8 MOUSE_DOWN=4
uint8 MOUSE_UP=5
std_msgs/msg/Header header
string client_id
string marker_name
string control_name
uint8 event_type
geometry_msgs/msg/Pose pose
uint32 menu_entry_id
geometry_msgs/msg/Point mouse_point
bool mouse_point_valid
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerInit)RB", R"RB(string server_id
uint64 seq_num
visualization_msgs/msg/InteractiveMarker[] markers
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerPose)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Pose pose
string name
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerUpdate)RB", R"RB(uint8 KEEP_ALIVE=0
uint8 UPDATE=1
string server_id
uint64 seq_num
uint8 type
visualization_msgs/msg/InteractiveMarker[] markers
visualization_msgs/msg/InteractiveMarkerPose[] poses
string[] erases
)RB"},
    {R"RB(visualization_msgs/msg/Marker)RB", R"RB(int32 ARROW=0
int32 CUBE=1
int32 SPHERE=2
int32 CYLINDER=3
int32 LINE_STRIP=4
int32 LINE_LIST=5
int32 CUBE_LIST=6
int32 SPHERE_LIST=7
int32 POINTS=8
int32 TEXT_VIEW_FACING=9
int32 MESH_RESOURCE=10
int32 TRIANGLE_LIST=11
int32 ADD=0
int32 MODIFY=0
int32 DELETE=2
int32 DELETEALL=3
std_msgs/msg/Header header
string ns
int32 id
int32 type
int32 action
geometry_msgs/msg/Pose pose
geometry_msgs/msg/Vector3 scale
std_msgs/msg/ColorRGBA color
builtin_interfaces/msg/Duration lifetime
bool frame_locked
geometry_msgs/msg/Point[] points
std_msgs/msg/ColorRGBA[] colors
string text
string mesh_resource
bool mesh_use_embedded_materials
)RB"},
    {R"RB(visualization_msgs/msg/MarkerArray)RB", R"RB(visualization_msgs/msg/Marker[] markers
)RB"},
    {R"RB(visualization_msgs/msg/MenuEntry)RB", R"RB(uint8 FEEDBACK=0
uint8 ROSRUN=1
uint8 ROSLAUNCH=2
uint32 id
uint32 parent_id
string title
string command
uint8 command_type
)RB"},
};

const GeneratedTypeDefinition kRos2GalacticTypes[] = {
    {R"RB(action_msgs/msg/GoalInfo)RB", R"RB(unique_identifier_msgs/msg/UUID goal_id
builtin_interfaces/msg/Time stamp
)RB"},
    {R"RB(action_msgs/msg/GoalStatus)RB", R"RB(int8 STATUS_UNKNOWN=0
int8 STATUS_ACCEPTED=1
int8 STATUS_EXECUTING=2
int8 STATUS_CANCELING=3
int8 STATUS_SUCCEEDED=4
int8 STATUS_CANCELED=5
int8 STATUS_ABORTED=6
action_msgs/msg/GoalInfo goal_info
int8 status
)RB"},
    {R"RB(action_msgs/msg/GoalStatusArray)RB", R"RB(action_msgs/msg/GoalStatus[] status_list
)RB"},
    {R"RB(actionlib_msgs/msg/GoalID)RB", R"RB(builtin_interfaces/msg/Time stamp
string id
)RB"},
    {R"RB(actionlib_msgs/msg/GoalStatus)RB", R"RB(uint8 PENDING=0
uint8 ACTIVE=1
uint8 PREEMPTED=2
uint8 SUCCEEDED=3
uint8 ABORTED=4
uint8 REJECTED=5
uint8 PREEMPTING=6
uint8 RECALLING=7
uint8 RECALLED=8
uint8 LOST=9
actionlib_msgs/msg/GoalID goal_id
uint8 status
string text
)RB"},
    {R"RB(actionlib_msgs/msg/GoalStatusArray)RB", R"RB(std_msgs/msg/Header header
actionlib_msgs/msg/GoalStatus[] status_list
)RB"},
    {R"RB(builtin_interfaces/msg/Duration)RB", R"RB(int32 sec
uint32 nanosec
)RB"},
    {R"RB(builtin_interfaces/msg/Time)RB", R"RB(int32 sec
uint32 nanosec
)RB"},
    {R"RB(diagnostic_msgs/msg/DiagnosticArray)RB", R"RB(std_msgs/msg/Header header
diagnostic_msgs/msg/DiagnosticStatus[] status
)RB"},
    {R"RB(diagnostic_msgs/msg/DiagnosticStatus)RB", R"RB(byte OK=0
byte WARN=1
byte ERROR=2
byte STALE=3
byte level
string name
string message
string hardware_id
diagnostic_msgs/msg/KeyValue[] values
)RB"},
    {R"RB(diagnostic_msgs/msg/KeyValue)RB", R"RB(string key
string value
)RB"},
    {R"RB(geometry_msgs/msg/Accel)RB", R"RB(geometry_msgs/msg/Vector3 linear
geometry_msgs/msg/Vector3 angular
)RB"},
    {R"RB(geometry_msgs/msg/AccelStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Accel accel
)RB"},
    {R"RB(geometry_msgs/msg/AccelWithCovariance)RB", R"RB(geometry_msgs/msg/Accel accel
float64[36] covariance
)RB"},
    {R"RB(geometry_msgs/msg/AccelWithCovarianceStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/AccelWithCovariance accel
)RB"},
    {R"RB(geometry_msgs/msg/Inertia)RB", R"RB(float64 m
geometry_msgs/msg/Vector3 com
float64 ixx
float64 ixy
float64 ixz
float64 iyy
float64 iyz
float64 izz
)RB"},
    {R"RB(geometry_msgs/msg/InertiaStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Inertia inertia
)RB"},
    {R"RB(geometry_msgs/msg/Point)RB", R"RB(float64 x
float64 y
float64 z
)RB"},
    {R"RB(geometry_msgs/msg/Point32)RB", R"RB(float32 x
float32 y
float32 z
)RB"},
    {R"RB(geometry_msgs/msg/PointStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Point point
)RB"},
    {R"RB(geometry_msgs/msg/Polygon)RB", R"RB(geometry_msgs/msg/Point32[] points
)RB"},
    {R"RB(geometry_msgs/msg/PolygonStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Polygon polygon
)RB"},
    {R"RB(geometry_msgs/msg/Pose)RB", R"RB(geometry_msgs/msg/Point position
geometry_msgs/msg/Quaternion orientation
)RB"},
    {R"RB(geometry_msgs/msg/Pose2D)RB", R"RB(float64 x
float64 y
float64 theta
)RB"},
    {R"RB(geometry_msgs/msg/PoseArray)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Pose[] poses
)RB"},
    {R"RB(geometry_msgs/msg/PoseStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Pose pose
)RB"},
    {R"RB(geometry_msgs/msg/PoseWithCovariance)RB", R"RB(geometry_msgs/msg/Pose pose
float64[36] covariance
)RB"},
    {R"RB(geometry_msgs/msg/PoseWithCovarianceStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/PoseWithCovariance pose
)RB"},
    {R"RB(geometry_msgs/msg/Quaternion)RB", R"RB(float64 x
float64 y
float64 z
float64 w
)RB"},
    {R"RB(geometry_msgs/msg/QuaternionStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Quaternion quaternion
)RB"},
    {R"RB(geometry_msgs/msg/Transform)RB", R"RB(geometry_msgs/msg/Vector3 translation
geometry_msgs/msg/Quaternion rotation
)RB"},
    {R"RB(geometry_msgs/msg/TransformStamped)RB", R"RB(std_msgs/msg/Header header
string child_frame_id
geometry_msgs/msg/Transform transform
)RB"},
    {R"RB(geometry_msgs/msg/Twist)RB", R"RB(geometry_msgs/msg/Vector3 linear
geometry_msgs/msg/Vector3 angular
)RB"},
    {R"RB(geometry_msgs/msg/TwistStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Twist twist
)RB"},
    {R"RB(geometry_msgs/msg/TwistWithCovariance)RB", R"RB(geometry_msgs/msg/Twist twist
float64[36] covariance
)RB"},
    {R"RB(geometry_msgs/msg/TwistWithCovarianceStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/TwistWithCovariance twist
)RB"},
    {R"RB(geometry_msgs/msg/Vector3)RB", R"RB(float64 x
float64 y
float64 z
)RB"},
    {R"RB(geometry_msgs/msg/Vector3Stamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Vector3 vector
)RB"},
    {R"RB(geometry_msgs/msg/Wrench)RB", R"RB(geometry_msgs/msg/Vector3 force
geometry_msgs/msg/Vector3 torque
)RB"},
    {R"RB(geometry_msgs/msg/WrenchStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Wrench wrench
)RB"},
    {R"RB(libstatistics_collector/msg/DummyMessage)RB", R"RB(std_msgs/msg/Header header
)RB"},
    {R"RB(lifecycle_msgs/msg/State)RB", R"RB(uint8 PRIMARY_STATE_UNKNOWN=0
uint8 PRIMARY_STATE_UNCONFIGURED=1
uint8 PRIMARY_STATE_INACTIVE=2
uint8 PRIMARY_STATE_ACTIVE=3
uint8 PRIMARY_STATE_FINALIZED=4
uint8 TRANSITION_STATE_CONFIGURING=10
uint8 TRANSITION_STATE_CLEANINGUP=11
uint8 TRANSITION_STATE_SHUTTINGDOWN=12
uint8 TRANSITION_STATE_ACTIVATING=13
uint8 TRANSITION_STATE_DEACTIVATING=14
uint8 TRANSITION_STATE_ERRORPROCESSING=15
uint8 id
string label
)RB"},
    {R"RB(lifecycle_msgs/msg/Transition)RB", R"RB(uint8 TRANSITION_CREATE=0
uint8 TRANSITION_CONFIGURE=1
uint8 TRANSITION_CLEANUP=2
uint8 TRANSITION_ACTIVATE=3
uint8 TRANSITION_DEACTIVATE=4
uint8 TRANSITION_UNCONFIGURED_SHUTDOWN=5
uint8 TRANSITION_INACTIVE_SHUTDOWN=6
uint8 TRANSITION_ACTIVE_SHUTDOWN=7
uint8 TRANSITION_DESTROY=8
uint8 TRANSITION_ON_CONFIGURE_SUCCESS=10
uint8 TRANSITION_ON_CONFIGURE_FAILURE=11
uint8 TRANSITION_ON_CONFIGURE_ERROR=12
uint8 TRANSITION_ON_CLEANUP_SUCCESS=20
uint8 TRANSITION_ON_CLEANUP_FAILURE=21
uint8 TRANSITION_ON_CLEANUP_ERROR=22
uint8 TRANSITION_ON_ACTIVATE_SUCCESS=30
uint8 TRANSITION_ON_ACTIVATE_FAILURE=31
uint8 TRANSITION_ON_ACTIVATE_ERROR=32
uint8 TRANSITION_ON_DEACTIVATE_SUCCESS=40
uint8 TRANSITION_ON_DEACTIVATE_FAILURE=41
uint8 TRANSITION_ON_DEACTIVATE_ERROR=42
uint8 TRANSITION_ON_SHUTDOWN_SUCCESS=50
uint8 TRANSITION_ON_SHUTDOWN_FAILURE=51
uint8 TRANSITION_ON_SHUTDOWN_ERROR=52
uint8 TRANSITION_ON_ERROR_SUCCESS=60
uint8 TRANSITION_ON_ERROR_FAILURE=61
uint8 TRANSITION_ON_ERROR_ERROR=62
uint8 TRANSITION_CALLBACK_SUCCESS=97
uint8 TRANSITION_CALLBACK_FAILURE=98
uint8 TRANSITION_CALLBACK_ERROR=99
uint8 id
string label
)RB"},
    {R"RB(lifecycle_msgs/msg/TransitionDescription)RB", R"RB(lifecycle_msgs/msg/Transition transition
lifecycle_msgs/msg/State start_state
lifecycle_msgs/msg/State goal_state
)RB"},
    {R"RB(lifecycle_msgs/msg/TransitionEvent)RB", R"RB(uint64 timestamp
lifecycle_msgs/msg/Transition transition
lifecycle_msgs/msg/State start_state
lifecycle_msgs/msg/State goal_state
)RB"},
    {R"RB(nav_msgs/msg/GridCells)RB", R"RB(std_msgs/msg/Header header
float32 cell_width
float32 cell_height
geometry_msgs/msg/Point[] cells
)RB"},
    {R"RB(nav_msgs/msg/MapMetaData)RB", R"RB(builtin_interfaces/msg/Time map_load_time
float32 resolution
uint32 width
uint32 height
geometry_msgs/msg/Pose origin
)RB"},
    {R"RB(nav_msgs/msg/OccupancyGrid)RB", R"RB(std_msgs/msg/Header header
nav_msgs/msg/MapMetaData info
int8[] data
)RB"},
    {R"RB(nav_msgs/msg/Odometry)RB", R"RB(std_msgs/msg/Header header
string child_frame_id
geometry_msgs/msg/PoseWithCovariance pose
geometry_msgs/msg/TwistWithCovariance twist
)RB"},
    {R"RB(nav_msgs/msg/Path)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/PoseStamped[] poses
)RB"},
    {R"RB(rcl_interfaces/msg/FloatingPointRange)RB", R"RB(float64 from_value
float64 to_value
float64 step
)RB"},
    {R"RB(rcl_interfaces/msg/IntegerRange)RB", R"RB(int64 from_value
int64 to_value
uint64 step
)RB"},
    {R"RB(rcl_interfaces/msg/ListParametersResult)RB", R"RB(string[] names
string[] prefixes
)RB"},
    {R"RB(rcl_interfaces/msg/Log)RB", R"RB(byte DEBUG=10
byte INFO=20
byte WARN=30
byte ERROR=40
byte FATAL=50
builtin_interfaces/msg/Time stamp
uint8 level
string name
string msg
string file
string function
uint32 line
)RB"},
    {R"RB(rcl_interfaces/msg/Parameter)RB", R"RB(string name
rcl_interfaces/msg/ParameterValue value
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterDescriptor)RB", R"RB(string name
uint8 type
string description
string additional_constraints
bool read_only
bool dynamic_typing
rcl_interfaces/msg/FloatingPointRange[<=1] floating_point_range
rcl_interfaces/msg/IntegerRange[<=1] integer_range
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterEvent)RB", R"RB(builtin_interfaces/msg/Time stamp
string node
rcl_interfaces/msg/Parameter[] new_parameters
rcl_interfaces/msg/Parameter[] changed_parameters
rcl_interfaces/msg/Parameter[] deleted_parameters
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterEventDescriptors)RB", R"RB(rcl_interfaces/msg/ParameterDescriptor[] new_parameters
rcl_interfaces/msg/ParameterDescriptor[] changed_parameters
rcl_interfaces/msg/ParameterDescriptor[] deleted_parameters
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterType)RB", R"RB(uint8 PARAMETER_NOT_SET=0
uint8 PARAMETER_BOOL=1
uint8 PARAMETER_INTEGER=2
uint8 PARAMETER_DOUBLE=3
uint8 PARAMETER_STRING=4
uint8 PARAMETER_BYTE_ARRAY=5
uint8 PARAMETER_BOOL_ARRAY=6
uint8 PARAMETER_INTEGER_ARRAY=7
uint8 PARAMETER_DOUBLE_ARRAY=8
uint8 PARAMETER_STRING_ARRAY=9
uint8 structure_needs_at_least_one_member
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterValue)RB", R"RB(uint8 type
bool bool_value
int64 integer_value
float64 double_value
string string_value
byte[] byte_array_value
bool[] bool_array_value
int64[] integer_array_value
float64[] double_array_value
string[] string_array_value
)RB"},
    {R"RB(rcl_interfaces/msg/SetParametersResult)RB", R"RB(bool successful
string reason
)RB"},
    {R"RB(rmw_dds_common/msg/Gid)RB", R"RB(char[24] data
)RB"},
    {R"RB(rmw_dds_common/msg/NodeEntitiesInfo)RB", R"RB(string<=256 node_namespace
string<=256 node_name
rmw_dds_common/msg/Gid[] reader_gid_seq
rmw_dds_common/msg/Gid[] writer_gid_seq
)RB"},
    {R"RB(rmw_dds_common/msg/ParticipantEntitiesInfo)RB", R"RB(rmw_dds_common/msg/Gid gid
rmw_dds_common/msg/NodeEntitiesInfo[] node_entities_info_seq
)RB"},
    {R"RB(rosgraph_msgs/msg/Clock)RB", R"RB(builtin_interfaces/msg/Time clock
)RB"},
    {R"RB(sensor_msgs/msg/BatteryState)RB", R"RB(uint8 POWER_SUPPLY_STATUS_UNKNOWN=0
uint8 POWER_SUPPLY_STATUS_CHARGING=1
uint8 POWER_SUPPLY_STATUS_DISCHARGING=2
uint8 POWER_SUPPLY_STATUS_NOT_CHARGING=3
uint8 POWER_SUPPLY_STATUS_FULL=4
uint8 POWER_SUPPLY_HEALTH_UNKNOWN=0
uint8 POWER_SUPPLY_HEALTH_GOOD=1
uint8 POWER_SUPPLY_HEALTH_OVERHEAT=2
uint8 POWER_SUPPLY_HEALTH_DEAD=3
uint8 POWER_SUPPLY_HEALTH_OVERVOLTAGE=4
uint8 POWER_SUPPLY_HEALTH_UNSPEC_FAILURE=5
uint8 POWER_SUPPLY_HEALTH_COLD=6
uint8 POWER_SUPPLY_HEALTH_WATCHDOG_TIMER_EXPIRE=7
uint8 POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE=8
uint8 POWER_SUPPLY_TECHNOLOGY_UNKNOWN=0
uint8 POWER_SUPPLY_TECHNOLOGY_NIMH=1
uint8 POWER_SUPPLY_TECHNOLOGY_LION=2
uint8 POWER_SUPPLY_TECHNOLOGY_LIPO=3
uint8 POWER_SUPPLY_TECHNOLOGY_LIFE=4
uint8 POWER_SUPPLY_TECHNOLOGY_NICD=5
uint8 POWER_SUPPLY_TECHNOLOGY_LIMN=6
std_msgs/msg/Header header
float32 voltage
float32 temperature
float32 current
float32 charge
float32 capacity
float32 design_capacity
float32 percentage
uint8 power_supply_status
uint8 power_supply_health
uint8 power_supply_technology
bool present
float32[] cell_voltage
float32[] cell_temperature
string location
string serial_number
)RB"},
    {R"RB(sensor_msgs/msg/CameraInfo)RB", R"RB(std_msgs/msg/Header header
uint32 height
uint32 width
string distortion_model
float64[] d
float64[9] k
float64[9] r
float64[12] p
uint32 binning_x
uint32 binning_y
sensor_msgs/msg/RegionOfInterest roi
)RB"},
    {R"RB(sensor_msgs/msg/ChannelFloat32)RB", R"RB(string name
float32[] values
)RB"},
    {R"RB(sensor_msgs/msg/CompressedImage)RB", R"RB(std_msgs/msg/Header header
string format
uint8[] data
)RB"},
    {R"RB(sensor_msgs/msg/FluidPressure)RB", R"RB(std_msgs/msg/Header header
float64 fluid_pressure
float64 variance
)RB"},
    {R"RB(sensor_msgs/msg/Illuminance)RB", R"RB(std_msgs/msg/Header header
float64 illuminance
float64 variance
)RB"},
    {R"RB(sensor_msgs/msg/Image)RB", R"RB(std_msgs/msg/Header header
uint32 height
uint32 width
string encoding
uint8 is_bigendian
uint32 step
uint8[] data
)RB"},
    {R"RB(sensor_msgs/msg/Imu)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Quaternion orientation
float64[9] orientation_covariance
geometry_msgs/msg/Vector3 angular_velocity
float64[9] angular_velocity_covariance
geometry_msgs/msg/Vector3 linear_acceleration
float64[9] linear_acceleration_covariance
)RB"},
    {R"RB(sensor_msgs/msg/JointState)RB", R"RB(std_msgs/msg/Header header
string[] name
float64[] position
float64[] velocity
float64[] effort
)RB"},
    {R"RB(sensor_msgs/msg/Joy)RB", R"RB(std_msgs/msg/Header header
float32[] axes
int32[] buttons
)RB"},
    {R"RB(sensor_msgs/msg/JoyFeedback)RB", R"RB(uint8 TYPE_LED=0
uint8 TYPE_RUMBLE=1
uint8 TYPE_BUZZER=2
uint8 type
uint8 id
float32 intensity
)RB"},
    {R"RB(sensor_msgs/msg/JoyFeedbackArray)RB", R"RB(sensor_msgs/msg/JoyFeedback[] array
)RB"},
    {R"RB(sensor_msgs/msg/LaserEcho)RB", R"RB(float32[] echoes
)RB"},
    {R"RB(sensor_msgs/msg/LaserScan)RB", R"RB(std_msgs/msg/Header header
float32 angle_min
float32 angle_max
float32 angle_increment
float32 time_increment
float32 scan_time
float32 range_min
float32 range_max
float32[] ranges
float32[] intensities
)RB"},
    {R"RB(sensor_msgs/msg/MagneticField)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Vector3 magnetic_field
float64[9] magnetic_field_covariance
)RB"},
    {R"RB(sensor_msgs/msg/MultiDOFJointState)RB", R"RB(std_msgs/msg/Header header
string[] joint_names
geometry_msgs/msg/Transform[] transforms
geometry_msgs/msg/Twist[] twist
geometry_msgs/msg/Wrench[] wrench
)RB"},
    {R"RB(sensor_msgs/msg/MultiEchoLaserScan)RB", R"RB(std_msgs/msg/Header header
float32 angle_min
float32 angle_max
float32 angle_increment
float32 time_increment
float32 scan_time
float32 range_min
float32 range_max
sensor_msgs/msg/LaserEcho[] ranges
sensor_msgs/msg/LaserEcho[] intensities
)RB"},
    {R"RB(sensor_msgs/msg/NavSatFix)RB", R"RB(uint8 COVARIANCE_TYPE_UNKNOWN=0
uint8 COVARIANCE_TYPE_APPROXIMATED=1
uint8 COVARIANCE_TYPE_DIAGONAL_KNOWN=2
uint8 COVARIANCE_TYPE_KNOWN=3
std_msgs/msg/Header header
sensor_msgs/msg/NavSatStatus status
float64 latitude
float64 longitude
float64 altitude
float64[9] position_covariance
uint8 position_covariance_type
)RB"},
    {R"RB(sensor_msgs/msg/NavSatStatus)RB", R"RB(int8 STATUS_NO_FIX=-1
int8 STATUS_FIX=0
int8 STATUS_SBAS_FIX=1
int8 STATUS_GBAS_FIX=2
uint16 SERVICE_GPS=1
uint16 SERVICE_GLONASS=2
uint16 SERVICE_COMPASS=4
uint16 SERVICE_GALILEO=8
int8 status
uint16 service
)RB"},
    {R"RB(sensor_msgs/msg/PointCloud)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Point32[] points
sensor_msgs/msg/ChannelFloat32[] channels
)RB"},
    {R"RB(sensor_msgs/msg/PointCloud2)RB", R"RB(std_msgs/msg/Header header
uint32 height
uint32 width
sensor_msgs/msg/PointField[] fields
bool is_bigendian
uint32 point_step
uint32 row_step
uint8[] data
bool is_dense
)RB"},
    {R"RB(sensor_msgs/msg/PointField)RB", R"RB(uint8 INT8=1
uint8 UINT8=2
uint8 INT16=3
uint8 UINT16=4
uint8 INT32=5
uint8 UINT32=6
uint8 FLOAT32=7
uint8 FLOAT64=8
string name
uint32 offset
uint8 datatype
uint32 count
)RB"},
    {R"RB(sensor_msgs/msg/Range)RB", R"RB(uint8 ULTRASOUND=0
uint8 INFRARED=1
std_msgs/msg/Header header
uint8 radiation_type
float32 field_of_view
float32 min_range
float32 max_range
float32 range
)RB"},
    {R"RB(sensor_msgs/msg/RegionOfInterest)RB", R"RB(uint32 x_offset
uint32 y_offset
uint32 height
uint32 width
bool do_rectify
)RB"},
    {R"RB(sensor_msgs/msg/RelativeHumidity)RB", R"RB(std_msgs/msg/Header header
float64 relative_humidity
float64 variance
)RB"},
    {R"RB(sensor_msgs/msg/Temperature)RB", R"RB(std_msgs/msg/Header header
float64 temperature
float64 variance
)RB"},
    {R"RB(sensor_msgs/msg/TimeReference)RB", R"RB(std_msgs/msg/Header header
builtin_interfaces/msg/Time time_ref
string source
)RB"},
    {R"RB(shape_msgs/msg/Mesh)RB", R"RB(shape_msgs/msg/MeshTriangle[] triangles
geometry_msgs/msg/Point[] vertices
)RB"},
    {R"RB(shape_msgs/msg/MeshTriangle)RB", R"RB(uint32[3] vertex_indices
)RB"},
    {R"RB(shape_msgs/msg/Plane)RB", R"RB(float64[4] coef
)RB"},
    {R"RB(shape_msgs/msg/SolidPrimitive)RB", R"RB(uint8 BOX=1
uint8 SPHERE=2
uint8 CYLINDER=3
uint8 CONE=4
uint8 BOX_X=0
uint8 BOX_Y=1
uint8 BOX_Z=2
uint8 SPHERE_RADIUS=0
uint8 CYLINDER_HEIGHT=0
uint8 CYLINDER_RADIUS=1
uint8 CONE_HEIGHT=0
uint8 CONE_RADIUS=1
uint8 type
float64[<=3] dimensions
)RB"},
    {R"RB(statistics_msgs/msg/MetricsMessage)RB", R"RB(string measurement_source_name
string metrics_source
string unit
builtin_interfaces/msg/Time window_start
builtin_interfaces/msg/Time window_stop
statistics_msgs/msg/StatisticDataPoint[] statistics
)RB"},
    {R"RB(statistics_msgs/msg/StatisticDataPoint)RB", R"RB(uint8 data_type
float64 data
)RB"},
    {R"RB(statistics_msgs/msg/StatisticDataType)RB", R"RB(uint8 STATISTICS_DATA_TYPE_UNINITIALIZED=0
uint8 STATISTICS_DATA_TYPE_AVERAGE=1
uint8 STATISTICS_DATA_TYPE_MINIMUM=2
uint8 STATISTICS_DATA_TYPE_MAXIMUM=3
uint8 STATISTICS_DATA_TYPE_STDDEV=4
uint8 STATISTICS_DATA_TYPE_SAMPLE_COUNT=5
uint8 structure_needs_at_least_one_member
)RB"},
    {R"RB(std_msgs/msg/Bool)RB", R"RB(bool data
)RB"},
    {R"RB(std_msgs/msg/Byte)RB", R"RB(byte data
)RB"},
    {R"RB(std_msgs/msg/ByteMultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
byte[] data
)RB"},
    {R"RB(std_msgs/msg/Char)RB", R"RB(char data
)RB"},
    {R"RB(std_msgs/msg/ColorRGBA)RB", R"RB(float32 r
float32 g
float32 b
float32 a
)RB"},
    {R"RB(std_msgs/msg/Empty)RB", R"RB(uint8 structure_needs_at_least_one_member
)RB"},
    {R"RB(std_msgs/msg/Float32)RB", R"RB(float32 data
)RB"},
    {R"RB(std_msgs/msg/Float32MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
float32[] data
)RB"},
    {R"RB(std_msgs/msg/Float64)RB", R"RB(float64 data
)RB"},
    {R"RB(std_msgs/msg/Float64MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
float64[] data
)RB"},
    {R"RB(std_msgs/msg/Header)RB", R"RB(builtin_interfaces/msg/Time stamp
string frame_id
)RB"},
    {R"RB(std_msgs/msg/Int16)RB", R"RB(int16 data
)RB"},
    {R"RB(std_msgs/msg/Int16MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
int16[] data
)RB"},
    {R"RB(std_msgs/msg/Int32)RB", R"RB(int32 data
)RB"},
    {R"RB(std_msgs/msg/Int32MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
int32[] data
)RB"},
    {R"RB(std_msgs/msg/Int64)RB", R"RB(int64 data
)RB"},
    {R"RB(std_msgs/msg/Int64MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
int64[] data
)RB"},
    {R"RB(std_msgs/msg/Int8)RB", R"RB(int8 data
)RB"},
    {R"RB(std_msgs/msg/Int8MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
int8[] data
)RB"},
    {R"RB(std_msgs/msg/MultiArrayDimension)RB", R"RB(string label
uint32 size
uint32 stride
)RB"},
    {R"RB(std_msgs/msg/MultiArrayLayout)RB", R"RB(std_msgs/msg/MultiArrayDimension[] dim
uint32 data_offset
)RB"},
    {R"RB(std_msgs/msg/String)RB", R"RB(string data
)RB"},
    {R"RB(std_msgs/msg/UInt16)RB", R"RB(uint16 data
)RB"},
    {R"RB(std_msgs/msg/UInt16MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
uint16[] data
)RB"},
    {R"RB(std_msgs/msg/UInt32)RB", R"RB(uint32 data
)RB"},
    {R"RB(std_msgs/msg/UInt32MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
uint32[] data
)RB"},
    {R"RB(std_msgs/msg/UInt64)RB", R"RB(uint64 data
)RB"},
    {R"RB(std_msgs/msg/UInt64MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
uint64[] data
)RB"},
    {R"RB(std_msgs/msg/UInt8)RB", R"RB(uint8 data
)RB"},
    {R"RB(std_msgs/msg/UInt8MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
uint8[] data
)RB"},
    {R"RB(stereo_msgs/msg/DisparityImage)RB", R"RB(std_msgs/msg/Header header
sensor_msgs/msg/Image image
float32 f
float32 t
sensor_msgs/msg/RegionOfInterest valid_window
float32 min_disparity
float32 max_disparity
float32 delta_d
)RB"},
    {R"RB(tf2_msgs/msg/TF2Error)RB", R"RB(uint8 NO_ERROR=0
uint8 LOOKUP_ERROR=1
uint8 CONNECTIVITY_ERROR=2
uint8 EXTRAPOLATION_ERROR=3
uint8 INVALID_ARGUMENT_ERROR=4
uint8 TIMEOUT_ERROR=5
uint8 TRANSFORM_ERROR=6
uint8 error
string error_string
)RB"},
    {R"RB(tf2_msgs/msg/TFMessage)RB", R"RB(geometry_msgs/msg/TransformStamped[] transforms
)RB"},
    {R"RB(trajectory_msgs/msg/JointTrajectory)RB", R"RB(std_msgs/msg/Header header
string[] joint_names
trajectory_msgs/msg/JointTrajectoryPoint[] points
)RB"},
    {R"RB(trajectory_msgs/msg/JointTrajectoryPoint)RB", R"RB(float64[] positions
float64[] velocities
float64[] accelerations
float64[] effort
builtin_interfaces/msg/Duration time_from_start
)RB"},
    {R"RB(trajectory_msgs/msg/MultiDOFJointTrajectory)RB", R"RB(std_msgs/msg/Header header
string[] joint_names
trajectory_msgs/msg/MultiDOFJointTrajectoryPoint[] points
)RB"},
    {R"RB(trajectory_msgs/msg/MultiDOFJointTrajectoryPoint)RB", R"RB(geometry_msgs/msg/Transform[] transforms
geometry_msgs/msg/Twist[] velocities
geometry_msgs/msg/Twist[] accelerations
builtin_interfaces/msg/Duration time_from_start
)RB"},
    {R"RB(unique_identifier_msgs/msg/UUID)RB", R"RB(uint8[16] uuid
)RB"},
    {R"RB(visualization_msgs/msg/ImageMarker)RB", R"RB(int32 CIRCLE=0
int32 LINE_STRIP=1
int32 LINE_LIST=2
int32 POLYGON=3
int32 POINTS=4
int32 ADD=0
int32 REMOVE=1
std_msgs/msg/Header header
string ns
int32 id
int32 type
int32 action
geometry_msgs/msg/Point position
float32 scale
std_msgs/msg/ColorRGBA outline_color
uint8 filled
std_msgs/msg/ColorRGBA fill_color
builtin_interfaces/msg/Duration lifetime
geometry_msgs/msg/Point[] points
std_msgs/msg/ColorRGBA[] outline_colors
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarker)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Pose pose
string name
string description
float32 scale
visualization_msgs/msg/MenuEntry[] menu_entries
visualization_msgs/msg/InteractiveMarkerControl[] controls
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerControl)RB", R"RB(uint8 INHERIT=0
uint8 FIXED=1
uint8 VIEW_FACING=2
uint8 NONE=0
uint8 MENU=1
uint8 BUTTON=2
uint8 MOVE_AXIS=3
uint8 MOVE_PLANE=4
uint8 ROTATE_AXIS=5
uint8 MOVE_ROTATE=6
uint8 MOVE_3D=7
uint8 ROTATE_3D=8
uint8 MOVE_ROTATE_3D=9
string name
geometry_msgs/msg/Quaternion orientation
uint8 orientation_mode
uint8 interaction_mode
bool always_visible
visualization_msgs/msg/Marker[] markers
bool independent_marker_orientation
string description
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerFeedback)RB", R"RB(uint8 KEEP_ALIVE=0
uint8 POSE_UPDATE=1
uint8 MENU_SELECT=2
uint8 BUTTON_CLICK=3
uint8 MOUSE_DOWN=4
uint8 MOUSE_UP=5
std_msgs/msg/Header header
string client_id
string marker_name
string control_name
uint8 event_type
geometry_msgs/msg/Pose pose
uint32 menu_entry_id
geometry_msgs/msg/Point mouse_point
bool mouse_point_valid
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerInit)RB", R"RB(string server_id
uint64 seq_num
visualization_msgs/msg/InteractiveMarker[] markers
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerPose)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Pose pose
string name
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerUpdate)RB", R"RB(uint8 KEEP_ALIVE=0
uint8 UPDATE=1
string server_id
uint64 seq_num
uint8 type
visualization_msgs/msg/InteractiveMarker[] markers
visualization_msgs/msg/InteractiveMarkerPose[] poses
string[] erases
)RB"},
    {R"RB(visualization_msgs/msg/Marker)RB", R"RB(int32 ARROW=0
int32 CUBE=1
int32 SPHERE=2
int32 CYLINDER=3
int32 LINE_STRIP=4
int32 LINE_LIST=5
int32 CUBE_LIST=6
int32 SPHERE_LIST=7
int32 POINTS=8
int32 TEXT_VIEW_FACING=9
int32 MESH_RESOURCE=10
int32 TRIANGLE_LIST=11
int32 ADD=0
int32 MODIFY=0
int32 DELETE=2
int32 DELETEALL=3
std_msgs/msg/Header header
string ns
int32 id
int32 type
int32 action
geometry_msgs/msg/Pose pose
geometry_msgs/msg/Vector3 scale
std_msgs/msg/ColorRGBA color
builtin_interfaces/msg/Duration lifetime
bool frame_locked
geometry_msgs/msg/Point[] points
std_msgs/msg/ColorRGBA[] colors
string text
string mesh_resource
bool mesh_use_embedded_materials
)RB"},
    {R"RB(visualization_msgs/msg/MarkerArray)RB", R"RB(visualization_msgs/msg/Marker[] markers
)RB"},
    {R"RB(visualization_msgs/msg/MenuEntry)RB", R"RB(uint8 FEEDBACK=0
uint8 ROSRUN=1
uint8 ROSLAUNCH=2
uint32 id
uint32 parent_id
string title
string command
uint8 command_type
)RB"},
};

const GeneratedTypeDefinition kRos2HumbleTypes[] = {
    {R"RB(action_msgs/msg/GoalInfo)RB", R"RB(unique_identifier_msgs/msg/UUID goal_id
builtin_interfaces/msg/Time stamp
)RB"},
    {R"RB(action_msgs/msg/GoalStatus)RB", R"RB(int8 STATUS_UNKNOWN=0
int8 STATUS_ACCEPTED=1
int8 STATUS_EXECUTING=2
int8 STATUS_CANCELING=3
int8 STATUS_SUCCEEDED=4
int8 STATUS_CANCELED=5
int8 STATUS_ABORTED=6
action_msgs/msg/GoalInfo goal_info
int8 status
)RB"},
    {R"RB(action_msgs/msg/GoalStatusArray)RB", R"RB(action_msgs/msg/GoalStatus[] status_list
)RB"},
    {R"RB(actionlib_msgs/msg/GoalID)RB", R"RB(builtin_interfaces/msg/Time stamp
string id
)RB"},
    {R"RB(actionlib_msgs/msg/GoalStatus)RB", R"RB(uint8 PENDING=0
uint8 ACTIVE=1
uint8 PREEMPTED=2
uint8 SUCCEEDED=3
uint8 ABORTED=4
uint8 REJECTED=5
uint8 PREEMPTING=6
uint8 RECALLING=7
uint8 RECALLED=8
uint8 LOST=9
actionlib_msgs/msg/GoalID goal_id
uint8 status
string text
)RB"},
    {R"RB(actionlib_msgs/msg/GoalStatusArray)RB", R"RB(std_msgs/msg/Header header
actionlib_msgs/msg/GoalStatus[] status_list
)RB"},
    {R"RB(builtin_interfaces/msg/Duration)RB", R"RB(int32 sec
uint32 nanosec
)RB"},
    {R"RB(builtin_interfaces/msg/Time)RB", R"RB(int32 sec
uint32 nanosec
)RB"},
    {R"RB(diagnostic_msgs/msg/DiagnosticArray)RB", R"RB(std_msgs/msg/Header header
diagnostic_msgs/msg/DiagnosticStatus[] status
)RB"},
    {R"RB(diagnostic_msgs/msg/DiagnosticStatus)RB", R"RB(byte OK=0
byte WARN=1
byte ERROR=2
byte STALE=3
byte level
string name
string message
string hardware_id
diagnostic_msgs/msg/KeyValue[] values
)RB"},
    {R"RB(diagnostic_msgs/msg/KeyValue)RB", R"RB(string key
string value
)RB"},
    {R"RB(geometry_msgs/msg/Accel)RB", R"RB(geometry_msgs/msg/Vector3 linear
geometry_msgs/msg/Vector3 angular
)RB"},
    {R"RB(geometry_msgs/msg/AccelStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Accel accel
)RB"},
    {R"RB(geometry_msgs/msg/AccelWithCovariance)RB", R"RB(geometry_msgs/msg/Accel accel
float64[36] covariance
)RB"},
    {R"RB(geometry_msgs/msg/AccelWithCovarianceStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/AccelWithCovariance accel
)RB"},
    {R"RB(geometry_msgs/msg/Inertia)RB", R"RB(float64 m
geometry_msgs/msg/Vector3 com
float64 ixx
float64 ixy
float64 ixz
float64 iyy
float64 iyz
float64 izz
)RB"},
    {R"RB(geometry_msgs/msg/InertiaStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Inertia inertia
)RB"},
    {R"RB(geometry_msgs/msg/Point)RB", R"RB(float64 x
float64 y
float64 z
)RB"},
    {R"RB(geometry_msgs/msg/Point32)RB", R"RB(float32 x
float32 y
float32 z
)RB"},
    {R"RB(geometry_msgs/msg/PointStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Point point
)RB"},
    {R"RB(geometry_msgs/msg/Polygon)RB", R"RB(geometry_msgs/msg/Point32[] points
)RB"},
    {R"RB(geometry_msgs/msg/PolygonStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Polygon polygon
)RB"},
    {R"RB(geometry_msgs/msg/Pose)RB", R"RB(geometry_msgs/msg/Point position
geometry_msgs/msg/Quaternion orientation
)RB"},
    {R"RB(geometry_msgs/msg/Pose2D)RB", R"RB(float64 x
float64 y
float64 theta
)RB"},
    {R"RB(geometry_msgs/msg/PoseArray)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Pose[] poses
)RB"},
    {R"RB(geometry_msgs/msg/PoseStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Pose pose
)RB"},
    {R"RB(geometry_msgs/msg/PoseWithCovariance)RB", R"RB(geometry_msgs/msg/Pose pose
float64[36] covariance
)RB"},
    {R"RB(geometry_msgs/msg/PoseWithCovarianceStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/PoseWithCovariance pose
)RB"},
    {R"RB(geometry_msgs/msg/Quaternion)RB", R"RB(float64 x
float64 y
float64 z
float64 w
)RB"},
    {R"RB(geometry_msgs/msg/QuaternionStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Quaternion quaternion
)RB"},
    {R"RB(geometry_msgs/msg/Transform)RB", R"RB(geometry_msgs/msg/Vector3 translation
geometry_msgs/msg/Quaternion rotation
)RB"},
    {R"RB(geometry_msgs/msg/TransformStamped)RB", R"RB(std_msgs/msg/Header header
string child_frame_id
geometry_msgs/msg/Transform transform
)RB"},
    {R"RB(geometry_msgs/msg/Twist)RB", R"RB(geometry_msgs/msg/Vector3 linear
geometry_msgs/msg/Vector3 angular
)RB"},
    {R"RB(geometry_msgs/msg/TwistStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Twist twist
)RB"},
    {R"RB(geometry_msgs/msg/TwistWithCovariance)RB", R"RB(geometry_msgs/msg/Twist twist
float64[36] covariance
)RB"},
    {R"RB(geometry_msgs/msg/TwistWithCovarianceStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/TwistWithCovariance twist
)RB"},
    {R"RB(geometry_msgs/msg/Vector3)RB", R"RB(float64 x
float64 y
float64 z
)RB"},
    {R"RB(geometry_msgs/msg/Vector3Stamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Vector3 vector
)RB"},
    {R"RB(geometry_msgs/msg/Wrench)RB", R"RB(geometry_msgs/msg/Vector3 force
geometry_msgs/msg/Vector3 torque
)RB"},
    {R"RB(geometry_msgs/msg/WrenchStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Wrench wrench
)RB"},
    {R"RB(lifecycle_msgs/msg/State)RB", R"RB(uint8 PRIMARY_STATE_UNKNOWN=0
uint8 PRIMARY_STATE_UNCONFIGURED=1
uint8 PRIMARY_STATE_INACTIVE=2
uint8 PRIMARY_STATE_ACTIVE=3
uint8 PRIMARY_STATE_FINALIZED=4
uint8 TRANSITION_STATE_CONFIGURING=10
uint8 TRANSITION_STATE_CLEANINGUP=11
uint8 TRANSITION_STATE_SHUTTINGDOWN=12
uint8 TRANSITION_STATE_ACTIVATING=13
uint8 TRANSITION_STATE_DEACTIVATING=14
uint8 TRANSITION_STATE_ERRORPROCESSING=15
uint8 id
string label
)RB"},
    {R"RB(lifecycle_msgs/msg/Transition)RB", R"RB(uint8 TRANSITION_CREATE=0
uint8 TRANSITION_CONFIGURE=1
uint8 TRANSITION_CLEANUP=2
uint8 TRANSITION_ACTIVATE=3
uint8 TRANSITION_DEACTIVATE=4
uint8 TRANSITION_UNCONFIGURED_SHUTDOWN=5
uint8 TRANSITION_INACTIVE_SHUTDOWN=6
uint8 TRANSITION_ACTIVE_SHUTDOWN=7
uint8 TRANSITION_DESTROY=8
uint8 TRANSITION_ON_CONFIGURE_SUCCESS=10
uint8 TRANSITION_ON_CONFIGURE_FAILURE=11
uint8 TRANSITION_ON_CONFIGURE_ERROR=12
uint8 TRANSITION_ON_CLEANUP_SUCCESS=20
uint8 TRANSITION_ON_CLEANUP_FAILURE=21
uint8 TRANSITION_ON_CLEANUP_ERROR=22
uint8 TRANSITION_ON_ACTIVATE_SUCCESS=30
uint8 TRANSITION_ON_ACTIVATE_FAILURE=31
uint8 TRANSITION_ON_ACTIVATE_ERROR=32
uint8 TRANSITION_ON_DEACTIVATE_SUCCESS=40
uint8 TRANSITION_ON_DEACTIVATE_FAILURE=41
uint8 TRANSITION_ON_DEACTIVATE_ERROR=42
uint8 TRANSITION_ON_SHUTDOWN_SUCCESS=50
uint8 TRANSITION_ON_SHUTDOWN_FAILURE=51
uint8 TRANSITION_ON_SHUTDOWN_ERROR=52
uint8 TRANSITION_ON_ERROR_SUCCESS=60
uint8 TRANSITION_ON_ERROR_FAILURE=61
uint8 TRANSITION_ON_ERROR_ERROR=62
uint8 TRANSITION_CALLBACK_SUCCESS=97
uint8 TRANSITION_CALLBACK_FAILURE=98
uint8 TRANSITION_CALLBACK_ERROR=99
uint8 id
string label
)RB"},
    {R"RB(lifecycle_msgs/msg/TransitionDescription)RB", R"RB(lifecycle_msgs/msg/Transition transition
lifecycle_msgs/msg/State start_state
lifecycle_msgs/msg/State goal_state
)RB"},
    {R"RB(lifecycle_msgs/msg/TransitionEvent)RB", R"RB(uint64 timestamp
lifecycle_msgs/msg/Transition transition
lifecycle_msgs/msg/State start_state
lifecycle_msgs/msg/State goal_state
)RB"},
    {R"RB(nav_msgs/msg/GridCells)RB", R"RB(std_msgs/msg/Header header
float32 cell_width
float32 cell_height
geometry_msgs/msg/Point[] cells
)RB"},
    {R"RB(nav_msgs/msg/MapMetaData)RB", R"RB(builtin_interfaces/msg/Time map_load_time
float32 resolution
uint32 width
uint32 height
geometry_msgs/msg/Pose origin
)RB"},
    {R"RB(nav_msgs/msg/OccupancyGrid)RB", R"RB(std_msgs/msg/Header header
nav_msgs/msg/MapMetaData info
int8[] data
)RB"},
    {R"RB(nav_msgs/msg/Odometry)RB", R"RB(std_msgs/msg/Header header
string child_frame_id
geometry_msgs/msg/PoseWithCovariance pose
geometry_msgs/msg/TwistWithCovariance twist
)RB"},
    {R"RB(nav_msgs/msg/Path)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/PoseStamped[] poses
)RB"},
    {R"RB(rcl_interfaces/msg/FloatingPointRange)RB", R"RB(float64 from_value
float64 to_value
float64 step
)RB"},
    {R"RB(rcl_interfaces/msg/IntegerRange)RB", R"RB(int64 from_value
int64 to_value
uint64 step
)RB"},
    {R"RB(rcl_interfaces/msg/ListParametersResult)RB", R"RB(string[] names
string[] prefixes
)RB"},
    {R"RB(rcl_interfaces/msg/Log)RB", R"RB(byte DEBUG=10
byte INFO=20
byte WARN=30
byte ERROR=40
byte FATAL=50
builtin_interfaces/msg/Time stamp
uint8 level
string name
string msg
string file
string function
uint32 line
)RB"},
    {R"RB(rcl_interfaces/msg/Parameter)RB", R"RB(string name
rcl_interfaces/msg/ParameterValue value
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterDescriptor)RB", R"RB(string name
uint8 type
string description
string additional_constraints
bool read_only
bool dynamic_typing
rcl_interfaces/msg/FloatingPointRange[<=1] floating_point_range
rcl_interfaces/msg/IntegerRange[<=1] integer_range
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterEvent)RB", R"RB(builtin_interfaces/msg/Time stamp
string node
rcl_interfaces/msg/Parameter[] new_parameters
rcl_interfaces/msg/Parameter[] changed_parameters
rcl_interfaces/msg/Parameter[] deleted_parameters
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterEventDescriptors)RB", R"RB(rcl_interfaces/msg/ParameterDescriptor[] new_parameters
rcl_interfaces/msg/ParameterDescriptor[] changed_parameters
rcl_interfaces/msg/ParameterDescriptor[] deleted_parameters
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterType)RB", R"RB(uint8 PARAMETER_NOT_SET=0
uint8 PARAMETER_BOOL=1
uint8 PARAMETER_INTEGER=2
uint8 PARAMETER_DOUBLE=3
uint8 PARAMETER_STRING=4
uint8 PARAMETER_BYTE_ARRAY=5
uint8 PARAMETER_BOOL_ARRAY=6
uint8 PARAMETER_INTEGER_ARRAY=7
uint8 PARAMETER_DOUBLE_ARRAY=8
uint8 PARAMETER_STRING_ARRAY=9
uint8 structure_needs_at_least_one_member
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterValue)RB", R"RB(uint8 type
bool bool_value
int64 integer_value
float64 double_value
string string_value
byte[] byte_array_value
bool[] bool_array_value
int64[] integer_array_value
float64[] double_array_value
string[] string_array_value
)RB"},
    {R"RB(rcl_interfaces/msg/SetParametersResult)RB", R"RB(bool successful
string reason
)RB"},
    {R"RB(rmw_dds_common/msg/Gid)RB", R"RB(char[24] data
)RB"},
    {R"RB(rmw_dds_common/msg/NodeEntitiesInfo)RB", R"RB(string<=256 node_namespace
string<=256 node_name
rmw_dds_common/msg/Gid[] reader_gid_seq
rmw_dds_common/msg/Gid[] writer_gid_seq
)RB"},
    {R"RB(rmw_dds_common/msg/ParticipantEntitiesInfo)RB", R"RB(rmw_dds_common/msg/Gid gid
rmw_dds_common/msg/NodeEntitiesInfo[] node_entities_info_seq
)RB"},
    {R"RB(rosbag2_interfaces/msg/ReadSplitEvent)RB", R"RB(string closed_file
string opened_file
)RB"},
    {R"RB(rosbag2_interfaces/msg/WriteSplitEvent)RB", R"RB(string closed_file
string opened_file
)RB"},
    {R"RB(rosgraph_msgs/msg/Clock)RB", R"RB(builtin_interfaces/msg/Time clock
)RB"},
    {R"RB(sensor_msgs/msg/BatteryState)RB", R"RB(uint8 POWER_SUPPLY_STATUS_UNKNOWN=0
uint8 POWER_SUPPLY_STATUS_CHARGING=1
uint8 POWER_SUPPLY_STATUS_DISCHARGING=2
uint8 POWER_SUPPLY_STATUS_NOT_CHARGING=3
uint8 POWER_SUPPLY_STATUS_FULL=4
uint8 POWER_SUPPLY_HEALTH_UNKNOWN=0
uint8 POWER_SUPPLY_HEALTH_GOOD=1
uint8 POWER_SUPPLY_HEALTH_OVERHEAT=2
uint8 POWER_SUPPLY_HEALTH_DEAD=3
uint8 POWER_SUPPLY_HEALTH_OVERVOLTAGE=4
uint8 POWER_SUPPLY_HEALTH_UNSPEC_FAILURE=5
uint8 POWER_SUPPLY_HEALTH_COLD=6
uint8 POWER_SUPPLY_HEALTH_WATCHDOG_TIMER_EXPIRE=7
uint8 POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE=8
uint8 POWER_SUPPLY_TECHNOLOGY_UNKNOWN=0
uint8 POWER_SUPPLY_TECHNOLOGY_NIMH=1
uint8 POWER_SUPPLY_TECHNOLOGY_LION=2
uint8 POWER_SUPPLY_TECHNOLOGY_LIPO=3
uint8 POWER_SUPPLY_TECHNOLOGY_LIFE=4
uint8 POWER_SUPPLY_TECHNOLOGY_NICD=5
uint8 POWER_SUPPLY_TECHNOLOGY_LIMN=6
std_msgs/msg/Header header
float32 voltage
float32 temperature
float32 current
float32 charge
float32 capacity
float32 design_capacity
float32 percentage
uint8 power_supply_status
uint8 power_supply_health
uint8 power_supply_technology
bool present
float32[] cell_voltage
float32[] cell_temperature
string location
string serial_number
)RB"},
    {R"RB(sensor_msgs/msg/CameraInfo)RB", R"RB(std_msgs/msg/Header header
uint32 height
uint32 width
string distortion_model
float64[] d
float64[9] k
float64[9] r
float64[12] p
uint32 binning_x
uint32 binning_y
sensor_msgs/msg/RegionOfInterest roi
)RB"},
    {R"RB(sensor_msgs/msg/ChannelFloat32)RB", R"RB(string name
float32[] values
)RB"},
    {R"RB(sensor_msgs/msg/CompressedImage)RB", R"RB(std_msgs/msg/Header header
string format
uint8[] data
)RB"},
    {R"RB(sensor_msgs/msg/FluidPressure)RB", R"RB(std_msgs/msg/Header header
float64 fluid_pressure
float64 variance
)RB"},
    {R"RB(sensor_msgs/msg/Illuminance)RB", R"RB(std_msgs/msg/Header header
float64 illuminance
float64 variance
)RB"},
    {R"RB(sensor_msgs/msg/Image)RB", R"RB(std_msgs/msg/Header header
uint32 height
uint32 width
string encoding
uint8 is_bigendian
uint32 step
uint8[] data
)RB"},
    {R"RB(sensor_msgs/msg/Imu)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Quaternion orientation
float64[9] orientation_covariance
geometry_msgs/msg/Vector3 angular_velocity
float64[9] angular_velocity_covariance
geometry_msgs/msg/Vector3 linear_acceleration
float64[9] linear_acceleration_covariance
)RB"},
    {R"RB(sensor_msgs/msg/JointState)RB", R"RB(std_msgs/msg/Header header
string[] name
float64[] position
float64[] velocity
float64[] effort
)RB"},
    {R"RB(sensor_msgs/msg/Joy)RB", R"RB(std_msgs/msg/Header header
float32[] axes
int32[] buttons
)RB"},
    {R"RB(sensor_msgs/msg/JoyFeedback)RB", R"RB(uint8 TYPE_LED=0
uint8 TYPE_RUMBLE=1
uint8 TYPE_BUZZER=2
uint8 type
uint8 id
float32 intensity
)RB"},
    {R"RB(sensor_msgs/msg/JoyFeedbackArray)RB", R"RB(sensor_msgs/msg/JoyFeedback[] array
)RB"},
    {R"RB(sensor_msgs/msg/LaserEcho)RB", R"RB(float32[] echoes
)RB"},
    {R"RB(sensor_msgs/msg/LaserScan)RB", R"RB(std_msgs/msg/Header header
float32 angle_min
float32 angle_max
float32 angle_increment
float32 time_increment
float32 scan_time
float32 range_min
float32 range_max
float32[] ranges
float32[] intensities
)RB"},
    {R"RB(sensor_msgs/msg/MagneticField)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Vector3 magnetic_field
float64[9] magnetic_field_covariance
)RB"},
    {R"RB(sensor_msgs/msg/MultiDOFJointState)RB", R"RB(std_msgs/msg/Header header
string[] joint_names
geometry_msgs/msg/Transform[] transforms
geometry_msgs/msg/Twist[] twist
geometry_msgs/msg/Wrench[] wrench
)RB"},
    {R"RB(sensor_msgs/msg/MultiEchoLaserScan)RB", R"RB(std_msgs/msg/Header header
float32 angle_min
float32 angle_max
float32 angle_increment
float32 time_increment
float32 scan_time
float32 range_min
float32 range_max
sensor_msgs/msg/LaserEcho[] ranges
sensor_msgs/msg/LaserEcho[] intensities
)RB"},
    {R"RB(sensor_msgs/msg/NavSatFix)RB", R"RB(uint8 COVARIANCE_TYPE_UNKNOWN=0
uint8 COVARIANCE_TYPE_APPROXIMATED=1
uint8 COVARIANCE_TYPE_DIAGONAL_KNOWN=2
uint8 COVARIANCE_TYPE_KNOWN=3
std_msgs/msg/Header header
sensor_msgs/msg/NavSatStatus status
float64 latitude
float64 longitude
float64 altitude
float64[9] position_covariance
uint8 position_covariance_type
)RB"},
    {R"RB(sensor_msgs/msg/NavSatStatus)RB", R"RB(int8 STATUS_NO_FIX=-1
int8 STATUS_FIX=0
int8 STATUS_SBAS_FIX=1
int8 STATUS_GBAS_FIX=2
uint16 SERVICE_GPS=1
uint16 SERVICE_GLONASS=2
uint16 SERVICE_COMPASS=4
uint16 SERVICE_GALILEO=8
int8 status
uint16 service
)RB"},
    {R"RB(sensor_msgs/msg/PointCloud)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Point32[] points
sensor_msgs/msg/ChannelFloat32[] channels
)RB"},
    {R"RB(sensor_msgs/msg/PointCloud2)RB", R"RB(std_msgs/msg/Header header
uint32 height
uint32 width
sensor_msgs/msg/PointField[] fields
bool is_bigendian
uint32 point_step
uint32 row_step
uint8[] data
bool is_dense
)RB"},
    {R"RB(sensor_msgs/msg/PointField)RB", R"RB(uint8 INT8=1
uint8 UINT8=2
uint8 INT16=3
uint8 UINT16=4
uint8 INT32=5
uint8 UINT32=6
uint8 FLOAT32=7
uint8 FLOAT64=8
string name
uint32 offset
uint8 datatype
uint32 count
)RB"},
    {R"RB(sensor_msgs/msg/Range)RB", R"RB(uint8 ULTRASOUND=0
uint8 INFRARED=1
std_msgs/msg/Header header
uint8 radiation_type
float32 field_of_view
float32 min_range
float32 max_range
float32 range
)RB"},
    {R"RB(sensor_msgs/msg/RegionOfInterest)RB", R"RB(uint32 x_offset
uint32 y_offset
uint32 height
uint32 width
bool do_rectify
)RB"},
    {R"RB(sensor_msgs/msg/RelativeHumidity)RB", R"RB(std_msgs/msg/Header header
float64 relative_humidity
float64 variance
)RB"},
    {R"RB(sensor_msgs/msg/Temperature)RB", R"RB(std_msgs/msg/Header header
float64 temperature
float64 variance
)RB"},
    {R"RB(sensor_msgs/msg/TimeReference)RB", R"RB(std_msgs/msg/Header header
builtin_interfaces/msg/Time time_ref
string source
)RB"},
    {R"RB(shape_msgs/msg/Mesh)RB", R"RB(shape_msgs/msg/MeshTriangle[] triangles
geometry_msgs/msg/Point[] vertices
)RB"},
    {R"RB(shape_msgs/msg/MeshTriangle)RB", R"RB(uint32[3] vertex_indices
)RB"},
    {R"RB(shape_msgs/msg/Plane)RB", R"RB(float64[4] coef
)RB"},
    {R"RB(shape_msgs/msg/SolidPrimitive)RB", R"RB(uint8 BOX=1
uint8 SPHERE=2
uint8 CYLINDER=3
uint8 CONE=4
uint8 PRISM=5
uint8 BOX_X=0
uint8 BOX_Y=1
uint8 BOX_Z=2
uint8 SPHERE_RADIUS=0
uint8 CYLINDER_HEIGHT=0
uint8 CYLINDER_RADIUS=1
uint8 CONE_HEIGHT=0
uint8 CONE_RADIUS=1
uint8 PRISM_HEIGHT=0
uint8 type
float64[<=3] dimensions
geometry_msgs/msg/Polygon polygon
)RB"},
    {R"RB(statistics_msgs/msg/MetricsMessage)RB", R"RB(string measurement_source_name
string metrics_source
string unit
builtin_interfaces/msg/Time window_start
builtin_interfaces/msg/Time window_stop
statistics_msgs/msg/StatisticDataPoint[] statistics
)RB"},
    {R"RB(statistics_msgs/msg/StatisticDataPoint)RB", R"RB(uint8 data_type
float64 data
)RB"},
    {R"RB(statistics_msgs/msg/StatisticDataType)RB", R"RB(uint8 STATISTICS_DATA_TYPE_UNINITIALIZED=0
uint8 STATISTICS_DATA_TYPE_AVERAGE=1
uint8 STATISTICS_DATA_TYPE_MINIMUM=2
uint8 STATISTICS_DATA_TYPE_MAXIMUM=3
uint8 STATISTICS_DATA_TYPE_STDDEV=4
uint8 STATISTICS_DATA_TYPE_SAMPLE_COUNT=5
uint8 structure_needs_at_least_one_member
)RB"},
    {R"RB(std_msgs/msg/Bool)RB", R"RB(bool data
)RB"},
    {R"RB(std_msgs/msg/Byte)RB", R"RB(byte data
)RB"},
    {R"RB(std_msgs/msg/ByteMultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
byte[] data
)RB"},
    {R"RB(std_msgs/msg/Char)RB", R"RB(char data
)RB"},
    {R"RB(std_msgs/msg/ColorRGBA)RB", R"RB(float32 r
float32 g
float32 b
float32 a
)RB"},
    {R"RB(std_msgs/msg/Empty)RB", R"RB(uint8 structure_needs_at_least_one_member
)RB"},
    {R"RB(std_msgs/msg/Float32)RB", R"RB(float32 data
)RB"},
    {R"RB(std_msgs/msg/Float32MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
float32[] data
)RB"},
    {R"RB(std_msgs/msg/Float64)RB", R"RB(float64 data
)RB"},
    {R"RB(std_msgs/msg/Float64MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
float64[] data
)RB"},
    {R"RB(std_msgs/msg/Header)RB", R"RB(builtin_interfaces/msg/Time stamp
string frame_id
)RB"},
    {R"RB(std_msgs/msg/Int16)RB", R"RB(int16 data
)RB"},
    {R"RB(std_msgs/msg/Int16MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
int16[] data
)RB"},
    {R"RB(std_msgs/msg/Int32)RB", R"RB(int32 data
)RB"},
    {R"RB(std_msgs/msg/Int32MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
int32[] data
)RB"},
    {R"RB(std_msgs/msg/Int64)RB", R"RB(int64 data
)RB"},
    {R"RB(std_msgs/msg/Int64MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
int64[] data
)RB"},
    {R"RB(std_msgs/msg/Int8)RB", R"RB(int8 data
)RB"},
    {R"RB(std_msgs/msg/Int8MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
int8[] data
)RB"},
    {R"RB(std_msgs/msg/MultiArrayDimension)RB", R"RB(string label
uint32 size
uint32 stride
)RB"},
    {R"RB(std_msgs/msg/MultiArrayLayout)RB", R"RB(std_msgs/msg/MultiArrayDimension[] dim
uint32 data_offset
)RB"},
    {R"RB(std_msgs/msg/String)RB", R"RB(string data
)RB"},
    {R"RB(std_msgs/msg/UInt16)RB", R"RB(uint16 data
)RB"},
    {R"RB(std_msgs/msg/UInt16MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
uint16[] data
)RB"},
    {R"RB(std_msgs/msg/UInt32)RB", R"RB(uint32 data
)RB"},
    {R"RB(std_msgs/msg/UInt32MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
uint32[] data
)RB"},
    {R"RB(std_msgs/msg/UInt64)RB", R"RB(uint64 data
)RB"},
    {R"RB(std_msgs/msg/UInt64MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
uint64[] data
)RB"},
    {R"RB(std_msgs/msg/UInt8)RB", R"RB(uint8 data
)RB"},
    {R"RB(std_msgs/msg/UInt8MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
uint8[] data
)RB"},
    {R"RB(stereo_msgs/msg/DisparityImage)RB", R"RB(std_msgs/msg/Header header
sensor_msgs/msg/Image image
float32 f
float32 t
sensor_msgs/msg/RegionOfInterest valid_window
float32 min_disparity
float32 max_disparity
float32 delta_d
)RB"},
    {R"RB(tf2_msgs/msg/TF2Error)RB", R"RB(uint8 NO_ERROR=0
uint8 LOOKUP_ERROR=1
uint8 CONNECTIVITY_ERROR=2
uint8 EXTRAPOLATION_ERROR=3
uint8 INVALID_ARGUMENT_ERROR=4
uint8 TIMEOUT_ERROR=5
uint8 TRANSFORM_ERROR=6
uint8 error
string error_string
)RB"},
    {R"RB(tf2_msgs/msg/TFMessage)RB", R"RB(geometry_msgs/msg/TransformStamped[] transforms
)RB"},
    {R"RB(trajectory_msgs/msg/JointTrajectory)RB", R"RB(std_msgs/msg/Header header
string[] joint_names
trajectory_msgs/msg/JointTrajectoryPoint[] points
)RB"},
    {R"RB(trajectory_msgs/msg/JointTrajectoryPoint)RB", R"RB(float64[] positions
float64[] velocities
float64[] accelerations
float64[] effort
builtin_interfaces/msg/Duration time_from_start
)RB"},
    {R"RB(trajectory_msgs/msg/MultiDOFJointTrajectory)RB", R"RB(std_msgs/msg/Header header
string[] joint_names
trajectory_msgs/msg/MultiDOFJointTrajectoryPoint[] points
)RB"},
    {R"RB(trajectory_msgs/msg/MultiDOFJointTrajectoryPoint)RB", R"RB(geometry_msgs/msg/Transform[] transforms
geometry_msgs/msg/Twist[] velocities
geometry_msgs/msg/Twist[] accelerations
builtin_interfaces/msg/Duration time_from_start
)RB"},
    {R"RB(unique_identifier_msgs/msg/UUID)RB", R"RB(uint8[16] uuid
)RB"},
    {R"RB(visualization_msgs/msg/ImageMarker)RB", R"RB(int32 CIRCLE=0
int32 LINE_STRIP=1
int32 LINE_LIST=2
int32 POLYGON=3
int32 POINTS=4
int32 ADD=0
int32 REMOVE=1
std_msgs/msg/Header header
string ns
int32 id
int32 type
int32 action
geometry_msgs/msg/Point position
float32 scale
std_msgs/msg/ColorRGBA outline_color
uint8 filled
std_msgs/msg/ColorRGBA fill_color
builtin_interfaces/msg/Duration lifetime
geometry_msgs/msg/Point[] points
std_msgs/msg/ColorRGBA[] outline_colors
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarker)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Pose pose
string name
string description
float32 scale
visualization_msgs/msg/MenuEntry[] menu_entries
visualization_msgs/msg/InteractiveMarkerControl[] controls
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerControl)RB", R"RB(uint8 INHERIT=0
uint8 FIXED=1
uint8 VIEW_FACING=2
uint8 NONE=0
uint8 MENU=1
uint8 BUTTON=2
uint8 MOVE_AXIS=3
uint8 MOVE_PLANE=4
uint8 ROTATE_AXIS=5
uint8 MOVE_ROTATE=6
uint8 MOVE_3D=7
uint8 ROTATE_3D=8
uint8 MOVE_ROTATE_3D=9
string name
geometry_msgs/msg/Quaternion orientation
uint8 orientation_mode
uint8 interaction_mode
bool always_visible
visualization_msgs/msg/Marker[] markers
bool independent_marker_orientation
string description
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerFeedback)RB", R"RB(uint8 KEEP_ALIVE=0
uint8 POSE_UPDATE=1
uint8 MENU_SELECT=2
uint8 BUTTON_CLICK=3
uint8 MOUSE_DOWN=4
uint8 MOUSE_UP=5
std_msgs/msg/Header header
string client_id
string marker_name
string control_name
uint8 event_type
geometry_msgs/msg/Pose pose
uint32 menu_entry_id
geometry_msgs/msg/Point mouse_point
bool mouse_point_valid
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerInit)RB", R"RB(string server_id
uint64 seq_num
visualization_msgs/msg/InteractiveMarker[] markers
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerPose)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Pose pose
string name
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerUpdate)RB", R"RB(uint8 KEEP_ALIVE=0
uint8 UPDATE=1
string server_id
uint64 seq_num
uint8 type
visualization_msgs/msg/InteractiveMarker[] markers
visualization_msgs/msg/InteractiveMarkerPose[] poses
string[] erases
)RB"},
    {R"RB(visualization_msgs/msg/Marker)RB", R"RB(int32 ARROW=0
int32 CUBE=1
int32 SPHERE=2
int32 CYLINDER=3
int32 LINE_STRIP=4
int32 LINE_LIST=5
int32 CUBE_LIST=6
int32 SPHERE_LIST=7
int32 POINTS=8
int32 TEXT_VIEW_FACING=9
int32 MESH_RESOURCE=10
int32 TRIANGLE_LIST=11
int32 ADD=0
int32 MODIFY=0
int32 DELETE=2
int32 DELETEALL=3
std_msgs/msg/Header header
string ns
int32 id
int32 type
int32 action
geometry_msgs/msg/Pose pose
geometry_msgs/msg/Vector3 scale
std_msgs/msg/ColorRGBA color
builtin_interfaces/msg/Duration lifetime
bool frame_locked
geometry_msgs/msg/Point[] points
std_msgs/msg/ColorRGBA[] colors
string texture_resource
sensor_msgs/msg/CompressedImage texture
visualization_msgs/msg/UVCoordinate[] uv_coordinates
string text
string mesh_resource
visualization_msgs/msg/MeshFile mesh_file
bool mesh_use_embedded_materials
)RB"},
    {R"RB(visualization_msgs/msg/MarkerArray)RB", R"RB(visualization_msgs/msg/Marker[] markers
)RB"},
    {R"RB(visualization_msgs/msg/MenuEntry)RB", R"RB(uint8 FEEDBACK=0
uint8 ROSRUN=1
uint8 ROSLAUNCH=2
uint32 id
uint32 parent_id
string title
string command
uint8 command_type
)RB"},
    {R"RB(visualization_msgs/msg/MeshFile)RB", R"RB(string filename
uint8[] data
)RB"},
    {R"RB(visualization_msgs/msg/UVCoordinate)RB", R"RB(float32 u
float32 v
)RB"},
};

const GeneratedTypeDefinition kRos2IronTypes[] = {
    {R"RB(action_msgs/msg/GoalInfo)RB", R"RB(unique_identifier_msgs/msg/UUID goal_id
builtin_interfaces/msg/Time stamp
)RB"},
    {R"RB(action_msgs/msg/GoalStatus)RB", R"RB(int8 STATUS_UNKNOWN=0
int8 STATUS_ACCEPTED=1
int8 STATUS_EXECUTING=2
int8 STATUS_CANCELING=3
int8 STATUS_SUCCEEDED=4
int8 STATUS_CANCELED=5
int8 STATUS_ABORTED=6
action_msgs/msg/GoalInfo goal_info
int8 status
)RB"},
    {R"RB(action_msgs/msg/GoalStatusArray)RB", R"RB(action_msgs/msg/GoalStatus[] status_list
)RB"},
    {R"RB(actionlib_msgs/msg/GoalID)RB", R"RB(builtin_interfaces/msg/Time stamp
string id
)RB"},
    {R"RB(actionlib_msgs/msg/GoalStatus)RB", R"RB(uint8 PENDING=0
uint8 ACTIVE=1
uint8 PREEMPTED=2
uint8 SUCCEEDED=3
uint8 ABORTED=4
uint8 REJECTED=5
uint8 PREEMPTING=6
uint8 RECALLING=7
uint8 RECALLED=8
uint8 LOST=9
actionlib_msgs/msg/GoalID goal_id
uint8 status
string text
)RB"},
    {R"RB(actionlib_msgs/msg/GoalStatusArray)RB", R"RB(std_msgs/msg/Header header
actionlib_msgs/msg/GoalStatus[] status_list
)RB"},
    {R"RB(builtin_interfaces/msg/Duration)RB", R"RB(int32 sec
uint32 nanosec
)RB"},
    {R"RB(builtin_interfaces/msg/Time)RB", R"RB(int32 sec
uint32 nanosec
)RB"},
    {R"RB(diagnostic_msgs/msg/DiagnosticArray)RB", R"RB(std_msgs/msg/Header header
diagnostic_msgs/msg/DiagnosticStatus[] status
)RB"},
    {R"RB(diagnostic_msgs/msg/DiagnosticStatus)RB", R"RB(byte OK=0
byte WARN=1
byte ERROR=2
byte STALE=3
byte level
string name
string message
string hardware_id
diagnostic_msgs/msg/KeyValue[] values
)RB"},
    {R"RB(diagnostic_msgs/msg/KeyValue)RB", R"RB(string key
string value
)RB"},
    {R"RB(geometry_msgs/msg/Accel)RB", R"RB(geometry_msgs/msg/Vector3 linear
geometry_msgs/msg/Vector3 angular
)RB"},
    {R"RB(geometry_msgs/msg/AccelStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Accel accel
)RB"},
    {R"RB(geometry_msgs/msg/AccelWithCovariance)RB", R"RB(geometry_msgs/msg/Accel accel
float64[36] covariance
)RB"},
    {R"RB(geometry_msgs/msg/AccelWithCovarianceStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/AccelWithCovariance accel
)RB"},
    {R"RB(geometry_msgs/msg/Inertia)RB", R"RB(float64 m
geometry_msgs/msg/Vector3 com
float64 ixx
float64 ixy
float64 ixz
float64 iyy
float64 iyz
float64 izz
)RB"},
    {R"RB(geometry_msgs/msg/InertiaStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Inertia inertia
)RB"},
    {R"RB(geometry_msgs/msg/Point)RB", R"RB(float64 x
float64 y
float64 z
)RB"},
    {R"RB(geometry_msgs/msg/Point32)RB", R"RB(float32 x
float32 y
float32 z
)RB"},
    {R"RB(geometry_msgs/msg/PointStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Point point
)RB"},
    {R"RB(geometry_msgs/msg/Polygon)RB", R"RB(geometry_msgs/msg/Point32[] points
)RB"},
    {R"RB(geometry_msgs/msg/PolygonStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Polygon polygon
)RB"},
    {R"RB(geometry_msgs/msg/Pose)RB", R"RB(geometry_msgs/msg/Point position
geometry_msgs/msg/Quaternion orientation
)RB"},
    {R"RB(geometry_msgs/msg/Pose2D)RB", R"RB(float64 x
float64 y
float64 theta
)RB"},
    {R"RB(geometry_msgs/msg/PoseArray)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Pose[] poses
)RB"},
    {R"RB(geometry_msgs/msg/PoseStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Pose pose
)RB"},
    {R"RB(geometry_msgs/msg/PoseWithCovariance)RB", R"RB(geometry_msgs/msg/Pose pose
float64[36] covariance
)RB"},
    {R"RB(geometry_msgs/msg/PoseWithCovarianceStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/PoseWithCovariance pose
)RB"},
    {R"RB(geometry_msgs/msg/Quaternion)RB", R"RB(float64 x
float64 y
float64 z
float64 w
)RB"},
    {R"RB(geometry_msgs/msg/QuaternionStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Quaternion quaternion
)RB"},
    {R"RB(geometry_msgs/msg/Transform)RB", R"RB(geometry_msgs/msg/Vector3 translation
geometry_msgs/msg/Quaternion rotation
)RB"},
    {R"RB(geometry_msgs/msg/TransformStamped)RB", R"RB(std_msgs/msg/Header header
string child_frame_id
geometry_msgs/msg/Transform transform
)RB"},
    {R"RB(geometry_msgs/msg/Twist)RB", R"RB(geometry_msgs/msg/Vector3 linear
geometry_msgs/msg/Vector3 angular
)RB"},
    {R"RB(geometry_msgs/msg/TwistStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Twist twist
)RB"},
    {R"RB(geometry_msgs/msg/TwistWithCovariance)RB", R"RB(geometry_msgs/msg/Twist twist
float64[36] covariance
)RB"},
    {R"RB(geometry_msgs/msg/TwistWithCovarianceStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/TwistWithCovariance twist
)RB"},
    {R"RB(geometry_msgs/msg/Vector3)RB", R"RB(float64 x
float64 y
float64 z
)RB"},
    {R"RB(geometry_msgs/msg/Vector3Stamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Vector3 vector
)RB"},
    {R"RB(geometry_msgs/msg/Wrench)RB", R"RB(geometry_msgs/msg/Vector3 force
geometry_msgs/msg/Vector3 torque
)RB"},
    {R"RB(geometry_msgs/msg/WrenchStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Wrench wrench
)RB"},
    {R"RB(lifecycle_msgs/msg/State)RB", R"RB(uint8 PRIMARY_STATE_UNKNOWN=0
uint8 PRIMARY_STATE_UNCONFIGURED=1
uint8 PRIMARY_STATE_INACTIVE=2
uint8 PRIMARY_STATE_ACTIVE=3
uint8 PRIMARY_STATE_FINALIZED=4
uint8 TRANSITION_STATE_CONFIGURING=10
uint8 TRANSITION_STATE_CLEANINGUP=11
uint8 TRANSITION_STATE_SHUTTINGDOWN=12
uint8 TRANSITION_STATE_ACTIVATING=13
uint8 TRANSITION_STATE_DEACTIVATING=14
uint8 TRANSITION_STATE_ERRORPROCESSING=15
uint8 id
string label
)RB"},
    {R"RB(lifecycle_msgs/msg/Transition)RB", R"RB(uint8 TRANSITION_CREATE=0
uint8 TRANSITION_CONFIGURE=1
uint8 TRANSITION_CLEANUP=2
uint8 TRANSITION_ACTIVATE=3
uint8 TRANSITION_DEACTIVATE=4
uint8 TRANSITION_UNCONFIGURED_SHUTDOWN=5
uint8 TRANSITION_INACTIVE_SHUTDOWN=6
uint8 TRANSITION_ACTIVE_SHUTDOWN=7
uint8 TRANSITION_DESTROY=8
uint8 TRANSITION_ON_CONFIGURE_SUCCESS=10
uint8 TRANSITION_ON_CONFIGURE_FAILURE=11
uint8 TRANSITION_ON_CONFIGURE_ERROR=12
uint8 TRANSITION_ON_CLEANUP_SUCCESS=20
uint8 TRANSITION_ON_CLEANUP_FAILURE=21
uint8 TRANSITION_ON_CLEANUP_ERROR=22
uint8 TRANSITION_ON_ACTIVATE_SUCCESS=30
uint8 TRANSITION_ON_ACTIVATE_FAILURE=31
uint8 TRANSITION_ON_ACTIVATE_ERROR=32
uint8 TRANSITION_ON_DEACTIVATE_SUCCESS=40
uint8 TRANSITION_ON_DEACTIVATE_FAILURE=41
uint8 TRANSITION_ON_DEACTIVATE_ERROR=42
uint8 TRANSITION_ON_SHUTDOWN_SUCCESS=50
uint8 TRANSITION_ON_SHUTDOWN_FAILURE=51
uint8 TRANSITION_ON_SHUTDOWN_ERROR=52
uint8 TRANSITION_ON_ERROR_SUCCESS=60
uint8 TRANSITION_ON_ERROR_FAILURE=61
uint8 TRANSITION_ON_ERROR_ERROR=62
uint8 TRANSITION_CALLBACK_SUCCESS=97
uint8 TRANSITION_CALLBACK_FAILURE=98
uint8 TRANSITION_CALLBACK_ERROR=99
uint8 id
string label
)RB"},
    {R"RB(lifecycle_msgs/msg/TransitionDescription)RB", R"RB(lifecycle_msgs/msg/Transition transition
lifecycle_msgs/msg/State start_state
lifecycle_msgs/msg/State goal_state
)RB"},
    {R"RB(lifecycle_msgs/msg/TransitionEvent)RB", R"RB(uint64 timestamp
lifecycle_msgs/msg/Transition transition
lifecycle_msgs/msg/State start_state
lifecycle_msgs/msg/State goal_state
)RB"},
    {R"RB(nav_msgs/msg/GridCells)RB", R"RB(std_msgs/msg/Header header
float32 cell_width
float32 cell_height
geometry_msgs/msg/Point[] cells
)RB"},
    {R"RB(nav_msgs/msg/MapMetaData)RB", R"RB(builtin_interfaces/msg/Time map_load_time
float32 resolution
uint32 width
uint32 height
geometry_msgs/msg/Pose origin
)RB"},
    {R"RB(nav_msgs/msg/OccupancyGrid)RB", R"RB(std_msgs/msg/Header header
nav_msgs/msg/MapMetaData info
int8[] data
)RB"},
    {R"RB(nav_msgs/msg/Odometry)RB", R"RB(std_msgs/msg/Header header
string child_frame_id
geometry_msgs/msg/PoseWithCovariance pose
geometry_msgs/msg/TwistWithCovariance twist
)RB"},
    {R"RB(nav_msgs/msg/Path)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/PoseStamped[] poses
)RB"},
    {R"RB(rcl_interfaces/msg/FloatingPointRange)RB", R"RB(float64 from_value
float64 to_value
float64 step
)RB"},
    {R"RB(rcl_interfaces/msg/IntegerRange)RB", R"RB(int64 from_value
int64 to_value
uint64 step
)RB"},
    {R"RB(rcl_interfaces/msg/ListParametersResult)RB", R"RB(string[] names
string[] prefixes
)RB"},
    {R"RB(rcl_interfaces/msg/Log)RB", R"RB(byte DEBUG=10
byte INFO=20
byte WARN=30
byte ERROR=40
byte FATAL=50
builtin_interfaces/msg/Time stamp
uint8 level
string name
string msg
string file
string function
uint32 line
)RB"},
    {R"RB(rcl_interfaces/msg/LoggerLevel)RB", R"RB(uint8 LOG_LEVEL_UNKNOWN=0
uint8 LOG_LEVEL_DEBUG=10
uint8 LOG_LEVEL_INFO=20
uint8 LOG_LEVEL_WARN=30
uint8 LOG_LEVEL_ERROR=40
uint8 LOG_LEVEL_FATAL=50
string name
uint32 level
)RB"},
    {R"RB(rcl_interfaces/msg/Parameter)RB", R"RB(string name
rcl_interfaces/msg/ParameterValue value
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterDescriptor)RB", R"RB(string name
uint8 type
string description
string additional_constraints
bool read_only
bool dynamic_typing
rcl_interfaces/msg/FloatingPointRange[<=1] floating_point_range
rcl_interfaces/msg/IntegerRange[<=1] integer_range
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterEvent)RB", R"RB(builtin_interfaces/msg/Time stamp
string node
rcl_interfaces/msg/Parameter[] new_parameters
rcl_interfaces/msg/Parameter[] changed_parameters
rcl_interfaces/msg/Parameter[] deleted_parameters
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterEventDescriptors)RB", R"RB(rcl_interfaces/msg/ParameterDescriptor[] new_parameters
rcl_interfaces/msg/ParameterDescriptor[] changed_parameters
rcl_interfaces/msg/ParameterDescriptor[] deleted_parameters
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterType)RB", R"RB(uint8 PARAMETER_NOT_SET=0
uint8 PARAMETER_BOOL=1
uint8 PARAMETER_INTEGER=2
uint8 PARAMETER_DOUBLE=3
uint8 PARAMETER_STRING=4
uint8 PARAMETER_BYTE_ARRAY=5
uint8 PARAMETER_BOOL_ARRAY=6
uint8 PARAMETER_INTEGER_ARRAY=7
uint8 PARAMETER_DOUBLE_ARRAY=8
uint8 PARAMETER_STRING_ARRAY=9
uint8 structure_needs_at_least_one_member
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterValue)RB", R"RB(uint8 type
bool bool_value
int64 integer_value
float64 double_value
string string_value
byte[] byte_array_value
bool[] bool_array_value
int64[] integer_array_value
float64[] double_array_value
string[] string_array_value
)RB"},
    {R"RB(rcl_interfaces/msg/SetLoggerLevelsResult)RB", R"RB(bool successful
string reason
)RB"},
    {R"RB(rcl_interfaces/msg/SetParametersResult)RB", R"RB(bool successful
string reason
)RB"},
    {R"RB(rmw_dds_common/msg/Gid)RB", R"RB(char[16] data
)RB"},
    {R"RB(rmw_dds_common/msg/NodeEntitiesInfo)RB", R"RB(string<=256 node_namespace
string<=256 node_name
rmw_dds_common/msg/Gid[] reader_gid_seq
rmw_dds_common/msg/Gid[] writer_gid_seq
)RB"},
    {R"RB(rmw_dds_common/msg/ParticipantEntitiesInfo)RB", R"RB(rmw_dds_common/msg/Gid gid
rmw_dds_common/msg/NodeEntitiesInfo[] node_entities_info_seq
)RB"},
    {R"RB(rosbag2_interfaces/msg/ReadSplitEvent)RB", R"RB(string closed_file
string opened_file
)RB"},
    {R"RB(rosbag2_interfaces/msg/WriteSplitEvent)RB", R"RB(string closed_file
string opened_file
)RB"},
    {R"RB(rosgraph_msgs/msg/Clock)RB", R"RB(builtin_interfaces/msg/Time clock
)RB"},
    {R"RB(sensor_msgs/msg/BatteryState)RB", R"RB(uint8 POWER_SUPPLY_STATUS_UNKNOWN=0
uint8 POWER_SUPPLY_STATUS_CHARGING=1
uint8 POWER_SUPPLY_STATUS_DISCHARGING=2
uint8 POWER_SUPPLY_STATUS_NOT_CHARGING=3
uint8 POWER_SUPPLY_STATUS_FULL=4
uint8 POWER_SUPPLY_HEALTH_UNKNOWN=0
uint8 POWER_SUPPLY_HEALTH_GOOD=1
uint8 POWER_SUPPLY_HEALTH_OVERHEAT=2
uint8 POWER_SUPPLY_HEALTH_DEAD=3
uint8 POWER_SUPPLY_HEALTH_OVERVOLTAGE=4
uint8 POWER_SUPPLY_HEALTH_UNSPEC_FAILURE=5
uint8 POWER_SUPPLY_HEALTH_COLD=6
uint8 POWER_SUPPLY_HEALTH_WATCHDOG_TIMER_EXPIRE=7
uint8 POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE=8
uint8 POWER_SUPPLY_TECHNOLOGY_UNKNOWN=0
uint8 POWER_SUPPLY_TECHNOLOGY_NIMH=1
uint8 POWER_SUPPLY_TECHNOLOGY_LION=2
uint8 POWER_SUPPLY_TECHNOLOGY_LIPO=3
uint8 POWER_SUPPLY_TECHNOLOGY_LIFE=4
uint8 POWER_SUPPLY_TECHNOLOGY_NICD=5
uint8 POWER_SUPPLY_TECHNOLOGY_LIMN=6
uint8 POWER_SUPPLY_TECHNOLOGY_TERNARY=7
uint8 POWER_SUPPLY_TECHNOLOGY_VRLA=8
std_msgs/msg/Header header
float32 voltage
float32 temperature
float32 current
float32 charge
float32 capacity
float32 design_capacity
float32 percentage
uint8 power_supply_status
uint8 power_supply_health
uint8 power_supply_technology
bool present
float32[] cell_voltage
float32[] cell_temperature
string location
string serial_number
)RB"},
    {R"RB(sensor_msgs/msg/CameraInfo)RB", R"RB(std_msgs/msg/Header header
uint32 height
uint32 width
string distortion_model
float64[] d
float64[9] k
float64[9] r
float64[12] p
uint32 binning_x
uint32 binning_y
sensor_msgs/msg/RegionOfInterest roi
)RB"},
    {R"RB(sensor_msgs/msg/ChannelFloat32)RB", R"RB(string name
float32[] values
)RB"},
    {R"RB(sensor_msgs/msg/CompressedImage)RB", R"RB(std_msgs/msg/Header header
string format
uint8[] data
)RB"},
    {R"RB(sensor_msgs/msg/FluidPressure)RB", R"RB(std_msgs/msg/Header header
float64 fluid_pressure
float64 variance
)RB"},
    {R"RB(sensor_msgs/msg/Illuminance)RB", R"RB(std_msgs/msg/Header header
float64 illuminance
float64 variance
)RB"},
    {R"RB(sensor_msgs/msg/Image)RB", R"RB(std_msgs/msg/Header header
uint32 height
uint32 width
string encoding
uint8 is_bigendian
uint32 step
uint8[] data
)RB"},
    {R"RB(sensor_msgs/msg/Imu)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Quaternion orientation
float64[9] orientation_covariance
geometry_msgs/msg/Vector3 angular_velocity
float64[9] angular_velocity_covariance
geometry_msgs/msg/Vector3 linear_acceleration
float64[9] linear_acceleration_covariance
)RB"},
    {R"RB(sensor_msgs/msg/JointState)RB", R"RB(std_msgs/msg/Header header
string[] name
float64[] position
float64[] velocity
float64[] effort
)RB"},
    {R"RB(sensor_msgs/msg/Joy)RB", R"RB(std_msgs/msg/Header header
float32[] axes
int32[] buttons
)RB"},
    {R"RB(sensor_msgs/msg/JoyFeedback)RB", R"RB(uint8 TYPE_LED=0
uint8 TYPE_RUMBLE=1
uint8 TYPE_BUZZER=2
uint8 type
uint8 id
float32 intensity
)RB"},
    {R"RB(sensor_msgs/msg/JoyFeedbackArray)RB", R"RB(sensor_msgs/msg/JoyFeedback[] array
)RB"},
    {R"RB(sensor_msgs/msg/LaserEcho)RB", R"RB(float32[] echoes
)RB"},
    {R"RB(sensor_msgs/msg/LaserScan)RB", R"RB(std_msgs/msg/Header header
float32 angle_min
float32 angle_max
float32 angle_increment
float32 time_increment
float32 scan_time
float32 range_min
float32 range_max
float32[] ranges
float32[] intensities
)RB"},
    {R"RB(sensor_msgs/msg/MagneticField)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Vector3 magnetic_field
float64[9] magnetic_field_covariance
)RB"},
    {R"RB(sensor_msgs/msg/MultiDOFJointState)RB", R"RB(std_msgs/msg/Header header
string[] joint_names
geometry_msgs/msg/Transform[] transforms
geometry_msgs/msg/Twist[] twist
geometry_msgs/msg/Wrench[] wrench
)RB"},
    {R"RB(sensor_msgs/msg/MultiEchoLaserScan)RB", R"RB(std_msgs/msg/Header header
float32 angle_min
float32 angle_max
float32 angle_increment
float32 time_increment
float32 scan_time
float32 range_min
float32 range_max
sensor_msgs/msg/LaserEcho[] ranges
sensor_msgs/msg/LaserEcho[] intensities
)RB"},
    {R"RB(sensor_msgs/msg/NavSatFix)RB", R"RB(uint8 COVARIANCE_TYPE_UNKNOWN=0
uint8 COVARIANCE_TYPE_APPROXIMATED=1
uint8 COVARIANCE_TYPE_DIAGONAL_KNOWN=2
uint8 COVARIANCE_TYPE_KNOWN=3
std_msgs/msg/Header header
sensor_msgs/msg/NavSatStatus status
float64 latitude
float64 longitude
float64 altitude
float64[9] position_covariance
uint8 position_covariance_type
)RB"},
    {R"RB(sensor_msgs/msg/NavSatStatus)RB", R"RB(int8 STATUS_NO_FIX=-1
int8 STATUS_FIX=0
int8 STATUS_SBAS_FIX=1
int8 STATUS_GBAS_FIX=2
uint16 SERVICE_GPS=1
uint16 SERVICE_GLONASS=2
uint16 SERVICE_COMPASS=4
uint16 SERVICE_GALILEO=8
int8 status
uint16 service
)RB"},
    {R"RB(sensor_msgs/msg/PointCloud)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Point32[] points
sensor_msgs/msg/ChannelFloat32[] channels
)RB"},
    {R"RB(sensor_msgs/msg/PointCloud2)RB", R"RB(std_msgs/msg/Header header
uint32 height
uint32 width
sensor_msgs/msg/PointField[] fields
bool is_bigendian
uint32 point_step
uint32 row_step
uint8[] data
bool is_dense
)RB"},
    {R"RB(sensor_msgs/msg/PointField)RB", R"RB(uint8 INT8=1
uint8 UINT8=2
uint8 INT16=3
uint8 UINT16=4
uint8 INT32=5
uint8 UINT32=6
uint8 FLOAT32=7
uint8 FLOAT64=8
string name
uint32 offset
uint8 datatype
uint32 count
)RB"},
    {R"RB(sensor_msgs/msg/Range)RB", R"RB(uint8 ULTRASOUND=0
uint8 INFRARED=1
std_msgs/msg/Header header
uint8 radiation_type
float32 field_of_view
float32 min_range
float32 max_range
float32 range
float32 variance
)RB"},
    {R"RB(sensor_msgs/msg/RegionOfInterest)RB", R"RB(uint32 x_offset
uint32 y_offset
uint32 height
uint32 width
bool do_rectify
)RB"},
    {R"RB(sensor_msgs/msg/RelativeHumidity)RB", R"RB(std_msgs/msg/Header header
float64 relative_humidity
float64 variance
)RB"},
    {R"RB(sensor_msgs/msg/Temperature)RB", R"RB(std_msgs/msg/Header header
float64 temperature
float64 variance
)RB"},
    {R"RB(sensor_msgs/msg/TimeReference)RB", R"RB(std_msgs/msg/Header header
builtin_interfaces/msg/Time time_ref
string source
)RB"},
    {R"RB(service_msgs/msg/ServiceEventInfo)RB", R"RB(uint8 REQUEST_SENT=0
uint8 REQUEST_RECEIVED=1
uint8 RESPONSE_SENT=2
uint8 RESPONSE_RECEIVED=3
uint8 event_type
builtin_interfaces/msg/Time stamp
char[16] client_gid
int64 sequence_number
)RB"},
    {R"RB(shape_msgs/msg/Mesh)RB", R"RB(shape_msgs/msg/MeshTriangle[] triangles
geometry_msgs/msg/Point[] vertices
)RB"},
    {R"RB(shape_msgs/msg/MeshTriangle)RB", R"RB(uint32[3] vertex_indices
)RB"},
    {R"RB(shape_msgs/msg/Plane)RB", R"RB(float64[4] coef
)RB"},
    {R"RB(shape_msgs/msg/SolidPrimitive)RB", R"RB(uint8 BOX=1
uint8 SPHERE=2
uint8 CYLINDER=3
uint8 CONE=4
uint8 PRISM=5
uint8 BOX_X=0
uint8 BOX_Y=1
uint8 BOX_Z=2
uint8 SPHERE_RADIUS=0
uint8 CYLINDER_HEIGHT=0
uint8 CYLINDER_RADIUS=1
uint8 CONE_HEIGHT=0
uint8 CONE_RADIUS=1
uint8 PRISM_HEIGHT=0
uint8 type
float64[<=3] dimensions
geometry_msgs/msg/Polygon polygon
)RB"},
    {R"RB(statistics_msgs/msg/MetricsMessage)RB", R"RB(string measurement_source_name
string metrics_source
string unit
builtin_interfaces/msg/Time window_start
builtin_interfaces/msg/Time window_stop
statistics_msgs/msg/StatisticDataPoint[] statistics
)RB"},
    {R"RB(statistics_msgs/msg/StatisticDataPoint)RB", R"RB(uint8 data_type
float64 data
)RB"},
    {R"RB(statistics_msgs/msg/StatisticDataType)RB", R"RB(uint8 STATISTICS_DATA_TYPE_UNINITIALIZED=0
uint8 STATISTICS_DATA_TYPE_AVERAGE=1
uint8 STATISTICS_DATA_TYPE_MINIMUM=2
uint8 STATISTICS_DATA_TYPE_MAXIMUM=3
uint8 STATISTICS_DATA_TYPE_STDDEV=4
uint8 STATISTICS_DATA_TYPE_SAMPLE_COUNT=5
uint8 structure_needs_at_least_one_member
)RB"},
    {R"RB(std_msgs/msg/Bool)RB", R"RB(bool data
)RB"},
    {R"RB(std_msgs/msg/Byte)RB", R"RB(byte data
)RB"},
    {R"RB(std_msgs/msg/ByteMultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
byte[] data
)RB"},
    {R"RB(std_msgs/msg/Char)RB", R"RB(char data
)RB"},
    {R"RB(std_msgs/msg/ColorRGBA)RB", R"RB(float32 r
float32 g
float32 b
float32 a
)RB"},
    {R"RB(std_msgs/msg/Empty)RB", R"RB(uint8 structure_needs_at_least_one_member
)RB"},
    {R"RB(std_msgs/msg/Float32)RB", R"RB(float32 data
)RB"},
    {R"RB(std_msgs/msg/Float32MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
float32[] data
)RB"},
    {R"RB(std_msgs/msg/Float64)RB", R"RB(float64 data
)RB"},
    {R"RB(std_msgs/msg/Float64MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
float64[] data
)RB"},
    {R"RB(std_msgs/msg/Header)RB", R"RB(builtin_interfaces/msg/Time stamp
string frame_id
)RB"},
    {R"RB(std_msgs/msg/Int16)RB", R"RB(int16 data
)RB"},
    {R"RB(std_msgs/msg/Int16MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
int16[] data
)RB"},
    {R"RB(std_msgs/msg/Int32)RB", R"RB(int32 data
)RB"},
    {R"RB(std_msgs/msg/Int32MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
int32[] data
)RB"},
    {R"RB(std_msgs/msg/Int64)RB", R"RB(int64 data
)RB"},
    {R"RB(std_msgs/msg/Int64MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
int64[] data
)RB"},
    {R"RB(std_msgs/msg/Int8)RB", R"RB(int8 data
)RB"},
    {R"RB(std_msgs/msg/Int8MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
int8[] data
)RB"},
    {R"RB(std_msgs/msg/MultiArrayDimension)RB", R"RB(string label
uint32 size
uint32 stride
)RB"},
    {R"RB(std_msgs/msg/MultiArrayLayout)RB", R"RB(std_msgs/msg/MultiArrayDimension[] dim
uint32 data_offset
)RB"},
    {R"RB(std_msgs/msg/String)RB", R"RB(string data
)RB"},
    {R"RB(std_msgs/msg/UInt16)RB", R"RB(uint16 data
)RB"},
    {R"RB(std_msgs/msg/UInt16MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
uint16[] data
)RB"},
    {R"RB(std_msgs/msg/UInt32)RB", R"RB(uint32 data
)RB"},
    {R"RB(std_msgs/msg/UInt32MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
uint32[] data
)RB"},
    {R"RB(std_msgs/msg/UInt64)RB", R"RB(uint64 data
)RB"},
    {R"RB(std_msgs/msg/UInt64MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
uint64[] data
)RB"},
    {R"RB(std_msgs/msg/UInt8)RB", R"RB(uint8 data
)RB"},
    {R"RB(std_msgs/msg/UInt8MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
uint8[] data
)RB"},
    {R"RB(stereo_msgs/msg/DisparityImage)RB", R"RB(std_msgs/msg/Header header
sensor_msgs/msg/Image image
float32 f
float32 t
sensor_msgs/msg/RegionOfInterest valid_window
float32 min_disparity
float32 max_disparity
float32 delta_d
)RB"},
    {R"RB(tf2_msgs/msg/TF2Error)RB", R"RB(uint8 NO_ERROR=0
uint8 LOOKUP_ERROR=1
uint8 CONNECTIVITY_ERROR=2
uint8 EXTRAPOLATION_ERROR=3
uint8 INVALID_ARGUMENT_ERROR=4
uint8 TIMEOUT_ERROR=5
uint8 TRANSFORM_ERROR=6
uint8 error
string error_string
)RB"},
    {R"RB(tf2_msgs/msg/TFMessage)RB", R"RB(geometry_msgs/msg/TransformStamped[] transforms
)RB"},
    {R"RB(trajectory_msgs/msg/JointTrajectory)RB", R"RB(std_msgs/msg/Header header
string[] joint_names
trajectory_msgs/msg/JointTrajectoryPoint[] points
)RB"},
    {R"RB(trajectory_msgs/msg/JointTrajectoryPoint)RB", R"RB(float64[] positions
float64[] velocities
float64[] accelerations
float64[] effort
builtin_interfaces/msg/Duration time_from_start
)RB"},
    {R"RB(trajectory_msgs/msg/MultiDOFJointTrajectory)RB", R"RB(std_msgs/msg/Header header
string[] joint_names
trajectory_msgs/msg/MultiDOFJointTrajectoryPoint[] points
)RB"},
    {R"RB(trajectory_msgs/msg/MultiDOFJointTrajectoryPoint)RB", R"RB(geometry_msgs/msg/Transform[] transforms
geometry_msgs/msg/Twist[] velocities
geometry_msgs/msg/Twist[] accelerations
builtin_interfaces/msg/Duration time_from_start
)RB"},
    {R"RB(type_description_interfaces/msg/Field)RB", R"RB(string name
type_description_interfaces/msg/FieldType type
string default_value
)RB"},
    {R"RB(type_description_interfaces/msg/FieldType)RB", R"RB(uint8 FIELD_TYPE_NOT_SET=0
uint8 FIELD_TYPE_NESTED_TYPE=1
uint8 FIELD_TYPE_INT8=2
uint8 FIELD_TYPE_UINT8=3
uint8 FIELD_TYPE_INT16=4
uint8 FIELD_TYPE_UINT16=5
uint8 FIELD_TYPE_INT32=6
uint8 FIELD_TYPE_UINT32=7
uint8 FIELD_TYPE_INT64=8
uint8 FIELD_TYPE_UINT64=9
uint8 FIELD_TYPE_FLOAT=10
uint8 FIELD_TYPE_DOUBLE=11
uint8 FIELD_TYPE_LONG_DOUBLE=12
uint8 FIELD_TYPE_CHAR=13
uint8 FIELD_TYPE_WCHAR=14
uint8 FIELD_TYPE_BOOLEAN=15
uint8 FIELD_TYPE_BYTE=16
uint8 FIELD_TYPE_STRING=17
uint8 FIELD_TYPE_WSTRING=18
uint8 FIELD_TYPE_FIXED_STRING=19
uint8 FIELD_TYPE_FIXED_WSTRING=20
uint8 FIELD_TYPE_BOUNDED_STRING=21
uint8 FIELD_TYPE_BOUNDED_WSTRING=22
uint8 FIELD_TYPE_NESTED_TYPE_ARRAY=49
uint8 FIELD_TYPE_INT8_ARRAY=50
uint8 FIELD_TYPE_UINT8_ARRAY=51
uint8 FIELD_TYPE_INT16_ARRAY=52
uint8 FIELD_TYPE_UINT16_ARRAY=53
uint8 FIELD_TYPE_INT32_ARRAY=54
uint8 FIELD_TYPE_UINT32_ARRAY=55
uint8 FIELD_TYPE_INT64_ARRAY=56
uint8 FIELD_TYPE_UINT64_ARRAY=57
uint8 FIELD_TYPE_FLOAT_ARRAY=58
uint8 FIELD_TYPE_DOUBLE_ARRAY=59
uint8 FIELD_TYPE_LONG_DOUBLE_ARRAY=60
uint8 FIELD_TYPE_CHAR_ARRAY=61
uint8 FIELD_TYPE_WCHAR_ARRAY=62
uint8 FIELD_TYPE_BOOLEAN_ARRAY=63
uint8 FIELD_TYPE_BYTE_ARRAY=64
uint8 FIELD_TYPE_STRING_ARRAY=65
uint8 FIELD_TYPE_WSTRING_ARRAY=66
uint8 FIELD_TYPE_FIXED_STRING_ARRAY=67
uint8 FIELD_TYPE_FIXED_WSTRING_ARRAY=68
uint8 FIELD_TYPE_BOUNDED_STRING_ARRAY=69
uint8 FIELD_TYPE_BOUNDED_WSTRING_ARRAY=70
uint8 FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE=97
uint8 FIELD_TYPE_INT8_BOUNDED_SEQUENCE=98
uint8 FIELD_TYPE_UINT8_BOUNDED_SEQUENCE=99
uint8 FIELD_TYPE_INT16_BOUNDED_SEQUENCE=100
uint8 FIELD_TYPE_UINT16_BOUNDED_SEQUENCE=101
uint8 FIELD_TYPE_INT32_BOUNDED_SEQUENCE=102
uint8 FIELD_TYPE_UINT32_BOUNDED_SEQUENCE=103
uint8 FIELD_TYPE_INT64_BOUNDED_SEQUENCE=104
uint8 FIELD_TYPE_UINT64_BOUNDED_SEQUENCE=105
uint8 FIELD_TYPE_FLOAT_BOUNDED_SEQUENCE=106
uint8 FIELD_TYPE_DOUBLE_BOUNDED_SEQUENCE=107
uint8 FIELD_TYPE_LONG_DOUBLE_BOUNDED_SEQUENCE=108
uint8 FIELD_TYPE_CHAR_BOUNDED_SEQUENCE=109
uint8 FIELD_TYPE_WCHAR_BOUNDED_SEQUENCE=110
uint8 FIELD_TYPE_BOOLEAN_BOUNDED_SEQUENCE=111
uint8 FIELD_TYPE_BYTE_BOUNDED_SEQUENCE=112
uint8 FIELD_TYPE_STRING_BOUNDED_SEQUENCE=113
uint8 FIELD_TYPE_WSTRING_BOUNDED_SEQUENCE=114
uint8 FIELD_TYPE_FIXED_STRING_BOUNDED_SEQUENCE=115
uint8 FIELD_TYPE_FIXED_WSTRING_BOUNDED_SEQUENCE=116
uint8 FIELD_TYPE_BOUNDED_STRING_BOUNDED_SEQUENCE=117
uint8 FIELD_TYPE_BOUNDED_WSTRING_BOUNDED_SEQUENCE=118
uint8 FIELD_TYPE_NESTED_TYPE_UNBOUNDED_SEQUENCE=145
uint8 FIELD_TYPE_INT8_UNBOUNDED_SEQUENCE=146
uint8 FIELD_TYPE_UINT8_UNBOUNDED_SEQUENCE=147
uint8 FIELD_TYPE_INT16_UNBOUNDED_SEQUENCE=148
uint8 FIELD_TYPE_UINT16_UNBOUNDED_SEQUENCE=149
uint8 FIELD_TYPE_INT32_UNBOUNDED_SEQUENCE=150
uint8 FIELD_TYPE_UINT32_UNBOUNDED_SEQUENCE=151
uint8 FIELD_TYPE_INT64_UNBOUNDED_SEQUENCE=152
uint8 FIELD_TYPE_UINT64_UNBOUNDED_SEQUENCE=153
uint8 FIELD_TYPE_FLOAT_UNBOUNDED_SEQUENCE=154
uint8 FIELD_TYPE_DOUBLE_UNBOUNDED_SEQUENCE=155
uint8 FIELD_TYPE_LONG_DOUBLE_UNBOUNDED_SEQUENCE=156
uint8 FIELD_TYPE_CHAR_UNBOUNDED_SEQUENCE=157
uint8 FIELD_TYPE_WCHAR_UNBOUNDED_SEQUENCE=158
uint8 FIELD_TYPE_BOOLEAN_UNBOUNDED_SEQUENCE=159
uint8 FIELD_TYPE_BYTE_UNBOUNDED_SEQUENCE=160
uint8 FIELD_TYPE_STRING_UNBOUNDED_SEQUENCE=161
uint8 FIELD_TYPE_WSTRING_UNBOUNDED_SEQUENCE=162
uint8 FIELD_TYPE_FIXED_STRING_UNBOUNDED_SEQUENCE=163
uint8 FIELD_TYPE_FIXED_WSTRING_UNBOUNDED_SEQUENCE=164
uint8 FIELD_TYPE_BOUNDED_STRING_UNBOUNDED_SEQUENCE=165
uint8 FIELD_TYPE_BOUNDED_WSTRING_UNBOUNDED_SEQUENCE=166
uint8 type_id
uint64 capacity
uint64 string_capacity
string<=255 nested_type_name
)RB"},
    {R"RB(type_description_interfaces/msg/IndividualTypeDescription)RB", R"RB(string<=255 type_name
type_description_interfaces/msg/Field[] fields
)RB"},
    {R"RB(type_description_interfaces/msg/KeyValue)RB", R"RB(string key
string value
)RB"},
    {R"RB(type_description_interfaces/msg/TypeDescription)RB", R"RB(type_description_interfaces/msg/IndividualTypeDescription type_description
type_description_interfaces/msg/IndividualTypeDescription[] referenced_type_descriptions
)RB"},
    {R"RB(type_description_interfaces/msg/TypeSource)RB", R"RB(string type_name
string encoding
string raw_file_contents
)RB"},
    {R"RB(unique_identifier_msgs/msg/UUID)RB", R"RB(uint8[16] uuid
)RB"},
    {R"RB(visualization_msgs/msg/ImageMarker)RB", R"RB(int32 CIRCLE=0
int32 LINE_STRIP=1
int32 LINE_LIST=2
int32 POLYGON=3
int32 POINTS=4
int32 ADD=0
int32 REMOVE=1
std_msgs/msg/Header header
string ns
int32 id
int32 type
int32 action
geometry_msgs/msg/Point position
float32 scale
std_msgs/msg/ColorRGBA outline_color
uint8 filled
std_msgs/msg/ColorRGBA fill_color
builtin_interfaces/msg/Duration lifetime
geometry_msgs/msg/Point[] points
std_msgs/msg/ColorRGBA[] outline_colors
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarker)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Pose pose
string name
string description
float32 scale
visualization_msgs/msg/MenuEntry[] menu_entries
visualization_msgs/msg/InteractiveMarkerControl[] controls
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerControl)RB", R"RB(uint8 INHERIT=0
uint8 FIXED=1
uint8 VIEW_FACING=2
uint8 NONE=0
uint8 MENU=1
uint8 BUTTON=2
uint8 MOVE_AXIS=3
uint8 MOVE_PLANE=4
uint8 ROTATE_AXIS=5
uint8 MOVE_ROTATE=6
uint8 MOVE_3D=7
uint8 ROTATE_3D=8
uint8 MOVE_ROTATE_3D=9
string name
geometry_msgs/msg/Quaternion orientation
uint8 orientation_mode
uint8 interaction_mode
bool always_visible
visualization_msgs/msg/Marker[] markers
bool independent_marker_orientation
string description
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerFeedback)RB", R"RB(uint8 KEEP_ALIVE=0
uint8 POSE_UPDATE=1
uint8 MENU_SELECT=2
uint8 BUTTON_CLICK=3
uint8 MOUSE_DOWN=4
uint8 MOUSE_UP=5
std_msgs/msg/Header header
string client_id
string marker_name
string control_name
uint8 event_type
geometry_msgs/msg/Pose pose
uint32 menu_entry_id
geometry_msgs/msg/Point mouse_point
bool mouse_point_valid
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerInit)RB", R"RB(string server_id
uint64 seq_num
visualization_msgs/msg/InteractiveMarker[] markers
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerPose)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Pose pose
string name
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerUpdate)RB", R"RB(uint8 KEEP_ALIVE=0
uint8 UPDATE=1
string server_id
uint64 seq_num
uint8 type
visualization_msgs/msg/InteractiveMarker[] markers
visualization_msgs/msg/InteractiveMarkerPose[] poses
string[] erases
)RB"},
    {R"RB(visualization_msgs/msg/Marker)RB", R"RB(int32 ARROW=0
int32 CUBE=1
int32 SPHERE=2
int32 CYLINDER=3
int32 LINE_STRIP=4
int32 LINE_LIST=5
int32 CUBE_LIST=6
int32 SPHERE_LIST=7
int32 POINTS=8
int32 TEXT_VIEW_FACING=9
int32 MESH_RESOURCE=10
int32 TRIANGLE_LIST=11
int32 ADD=0
int32 MODIFY=0
int32 DELETE=2
int32 DELETEALL=3
std_msgs/msg/Header header
string ns
int32 id
int32 type
int32 action
geometry_msgs/msg/Pose pose
geometry_msgs/msg/Vector3 scale
std_msgs/msg/ColorRGBA color
builtin_interfaces/msg/Duration lifetime
bool frame_locked
geometry_msgs/msg/Point[] points
std_msgs/msg/ColorRGBA[] colors
string texture_resource
sensor_msgs/msg/CompressedImage texture
visualization_msgs/msg/UVCoordinate[] uv_coordinates
string text
string mesh_resource
visualization_msgs/msg/MeshFile mesh_file
bool mesh_use_embedded_materials
)RB"},
    {R"RB(visualization_msgs/msg/MarkerArray)RB", R"RB(visualization_msgs/msg/Marker[] markers
)RB"},
    {R"RB(visualization_msgs/msg/MenuEntry)RB", R"RB(uint8 FEEDBACK=0
uint8 ROSRUN=1
uint8 ROSLAUNCH=2
uint32 id
uint32 parent_id
string title
string command
uint8 command_type
)RB"},
    {R"RB(visualization_msgs/msg/MeshFile)RB", R"RB(string filename
uint8[] data
)RB"},
    {R"RB(visualization_msgs/msg/UVCoordinate)RB", R"RB(float32 u
float32 v
)RB"},
};

const GeneratedTypeDefinition kRos2JazzyTypes[] = {
    {R"RB(action_msgs/msg/GoalInfo)RB", R"RB(unique_identifier_msgs/msg/UUID goal_id
builtin_interfaces/msg/Time stamp
)RB"},
    {R"RB(action_msgs/msg/GoalStatus)RB", R"RB(int8 STATUS_UNKNOWN=0
int8 STATUS_ACCEPTED=1
int8 STATUS_EXECUTING=2
int8 STATUS_CANCELING=3
int8 STATUS_SUCCEEDED=4
int8 STATUS_CANCELED=5
int8 STATUS_ABORTED=6
action_msgs/msg/GoalInfo goal_info
int8 status
)RB"},
    {R"RB(action_msgs/msg/GoalStatusArray)RB", R"RB(action_msgs/msg/GoalStatus[] status_list
)RB"},
    {R"RB(actionlib_msgs/msg/GoalID)RB", R"RB(builtin_interfaces/msg/Time stamp
string id
)RB"},
    {R"RB(actionlib_msgs/msg/GoalStatus)RB", R"RB(uint8 PENDING=0
uint8 ACTIVE=1
uint8 PREEMPTED=2
uint8 SUCCEEDED=3
uint8 ABORTED=4
uint8 REJECTED=5
uint8 PREEMPTING=6
uint8 RECALLING=7
uint8 RECALLED=8
uint8 LOST=9
actionlib_msgs/msg/GoalID goal_id
uint8 status
string text
)RB"},
    {R"RB(actionlib_msgs/msg/GoalStatusArray)RB", R"RB(std_msgs/msg/Header header
actionlib_msgs/msg/GoalStatus[] status_list
)RB"},
    {R"RB(builtin_interfaces/msg/Duration)RB", R"RB(int32 sec
uint32 nanosec
)RB"},
    {R"RB(builtin_interfaces/msg/Time)RB", R"RB(int32 sec
uint32 nanosec
)RB"},
    {R"RB(diagnostic_msgs/msg/DiagnosticArray)RB", R"RB(std_msgs/msg/Header header
diagnostic_msgs/msg/DiagnosticStatus[] status
)RB"},
    {R"RB(diagnostic_msgs/msg/DiagnosticStatus)RB", R"RB(byte OK=0
byte WARN=1
byte ERROR=2
byte STALE=3
byte level
string name
string message
string hardware_id
diagnostic_msgs/msg/KeyValue[] values
)RB"},
    {R"RB(diagnostic_msgs/msg/KeyValue)RB", R"RB(string key
string value
)RB"},
    {R"RB(geometry_msgs/msg/Accel)RB", R"RB(geometry_msgs/msg/Vector3 linear
geometry_msgs/msg/Vector3 angular
)RB"},
    {R"RB(geometry_msgs/msg/AccelStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Accel accel
)RB"},
    {R"RB(geometry_msgs/msg/AccelWithCovariance)RB", R"RB(geometry_msgs/msg/Accel accel
float64[36] covariance
)RB"},
    {R"RB(geometry_msgs/msg/AccelWithCovarianceStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/AccelWithCovariance accel
)RB"},
    {R"RB(geometry_msgs/msg/Inertia)RB", R"RB(float64 m
geometry_msgs/msg/Vector3 com
float64 ixx
float64 ixy
float64 ixz
float64 iyy
float64 iyz
float64 izz
)RB"},
    {R"RB(geometry_msgs/msg/InertiaStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Inertia inertia
)RB"},
    {R"RB(geometry_msgs/msg/Point)RB", R"RB(float64 x
float64 y
float64 z
)RB"},
    {R"RB(geometry_msgs/msg/Point32)RB", R"RB(float32 x
float32 y
float32 z
)RB"},
    {R"RB(geometry_msgs/msg/PointStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Point point
)RB"},
    {R"RB(geometry_msgs/msg/Polygon)RB", R"RB(geometry_msgs/msg/Point32[] points
)RB"},
    {R"RB(geometry_msgs/msg/PolygonInstance)RB", R"RB(geometry_msgs/msg/Polygon polygon
int64 id
)RB"},
    {R"RB(geometry_msgs/msg/PolygonInstanceStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/PolygonInstance polygon
)RB"},
    {R"RB(geometry_msgs/msg/PolygonStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Polygon polygon
)RB"},
    {R"RB(geometry_msgs/msg/Pose)RB", R"RB(geometry_msgs/msg/Point position
geometry_msgs/msg/Quaternion orientation
)RB"},
    {R"RB(geometry_msgs/msg/Pose2D)RB", R"RB(float64 x
float64 y
float64 theta
)RB"},
    {R"RB(geometry_msgs/msg/PoseArray)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Pose[] poses
)RB"},
    {R"RB(geometry_msgs/msg/PoseStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Pose pose
)RB"},
    {R"RB(geometry_msgs/msg/PoseWithCovariance)RB", R"RB(geometry_msgs/msg/Pose pose
float64[36] covariance
)RB"},
    {R"RB(geometry_msgs/msg/PoseWithCovarianceStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/PoseWithCovariance pose
)RB"},
    {R"RB(geometry_msgs/msg/Quaternion)RB", R"RB(float64 x
float64 y
float64 z
float64 w
)RB"},
    {R"RB(geometry_msgs/msg/QuaternionStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Quaternion quaternion
)RB"},
    {R"RB(geometry_msgs/msg/Transform)RB", R"RB(geometry_msgs/msg/Vector3 translation
geometry_msgs/msg/Quaternion rotation
)RB"},
    {R"RB(geometry_msgs/msg/TransformStamped)RB", R"RB(std_msgs/msg/Header header
string child_frame_id
geometry_msgs/msg/Transform transform
)RB"},
    {R"RB(geometry_msgs/msg/Twist)RB", R"RB(geometry_msgs/msg/Vector3 linear
geometry_msgs/msg/Vector3 angular
)RB"},
    {R"RB(geometry_msgs/msg/TwistStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Twist twist
)RB"},
    {R"RB(geometry_msgs/msg/TwistWithCovariance)RB", R"RB(geometry_msgs/msg/Twist twist
float64[36] covariance
)RB"},
    {R"RB(geometry_msgs/msg/TwistWithCovarianceStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/TwistWithCovariance twist
)RB"},
    {R"RB(geometry_msgs/msg/Vector3)RB", R"RB(float64 x
float64 y
float64 z
)RB"},
    {R"RB(geometry_msgs/msg/Vector3Stamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Vector3 vector
)RB"},
    {R"RB(geometry_msgs/msg/VelocityStamped)RB", R"RB(std_msgs/msg/Header header
string body_frame_id
string reference_frame_id
geometry_msgs/msg/Twist velocity
)RB"},
    {R"RB(geometry_msgs/msg/Wrench)RB", R"RB(geometry_msgs/msg/Vector3 force
geometry_msgs/msg/Vector3 torque
)RB"},
    {R"RB(geometry_msgs/msg/WrenchStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Wrench wrench
)RB"},
    {R"RB(lifecycle_msgs/msg/State)RB", R"RB(uint8 PRIMARY_STATE_UNKNOWN=0
uint8 PRIMARY_STATE_UNCONFIGURED=1
uint8 PRIMARY_STATE_INACTIVE=2
uint8 PRIMARY_STATE_ACTIVE=3
uint8 PRIMARY_STATE_FINALIZED=4
uint8 TRANSITION_STATE_CONFIGURING=10
uint8 TRANSITION_STATE_CLEANINGUP=11
uint8 TRANSITION_STATE_SHUTTINGDOWN=12
uint8 TRANSITION_STATE_ACTIVATING=13
uint8 TRANSITION_STATE_DEACTIVATING=14
uint8 TRANSITION_STATE_ERRORPROCESSING=15
uint8 id
string label
)RB"},
    {R"RB(lifecycle_msgs/msg/Transition)RB", R"RB(uint8 TRANSITION_CREATE=0
uint8 TRANSITION_CONFIGURE=1
uint8 TRANSITION_CLEANUP=2
uint8 TRANSITION_ACTIVATE=3
uint8 TRANSITION_DEACTIVATE=4
uint8 TRANSITION_UNCONFIGURED_SHUTDOWN=5
uint8 TRANSITION_INACTIVE_SHUTDOWN=6
uint8 TRANSITION_ACTIVE_SHUTDOWN=7
uint8 TRANSITION_DESTROY=8
uint8 TRANSITION_ON_CONFIGURE_SUCCESS=10
uint8 TRANSITION_ON_CONFIGURE_FAILURE=11
uint8 TRANSITION_ON_CONFIGURE_ERROR=12
uint8 TRANSITION_ON_CLEANUP_SUCCESS=20
uint8 TRANSITION_ON_CLEANUP_FAILURE=21
uint8 TRANSITION_ON_CLEANUP_ERROR=22
uint8 TRANSITION_ON_ACTIVATE_SUCCESS=30
uint8 TRANSITION_ON_ACTIVATE_FAILURE=31
uint8 TRANSITION_ON_ACTIVATE_ERROR=32
uint8 TRANSITION_ON_DEACTIVATE_SUCCESS=40
uint8 TRANSITION_ON_DEACTIVATE_FAILURE=41
uint8 TRANSITION_ON_DEACTIVATE_ERROR=42
uint8 TRANSITION_ON_SHUTDOWN_SUCCESS=50
uint8 TRANSITION_ON_SHUTDOWN_FAILURE=51
uint8 TRANSITION_ON_SHUTDOWN_ERROR=52
uint8 TRANSITION_ON_ERROR_SUCCESS=60
uint8 TRANSITION_ON_ERROR_FAILURE=61
uint8 TRANSITION_ON_ERROR_ERROR=62
uint8 TRANSITION_CALLBACK_SUCCESS=97
uint8 TRANSITION_CALLBACK_FAILURE=98
uint8 TRANSITION_CALLBACK_ERROR=99
uint8 id
string label
)RB"},
    {R"RB(lifecycle_msgs/msg/TransitionDescription)RB", R"RB(lifecycle_msgs/msg/Transition transition
lifecycle_msgs/msg/State start_state
lifecycle_msgs/msg/State goal_state
)RB"},
    {R"RB(lifecycle_msgs/msg/TransitionEvent)RB", R"RB(uint64 timestamp
lifecycle_msgs/msg/Transition transition
lifecycle_msgs/msg/State start_state
lifecycle_msgs/msg/State goal_state
)RB"},
    {R"RB(nav_msgs/msg/GridCells)RB", R"RB(std_msgs/msg/Header header
float32 cell_width
float32 cell_height
geometry_msgs/msg/Point[] cells
)RB"},
    {R"RB(nav_msgs/msg/MapMetaData)RB", R"RB(builtin_interfaces/msg/Time map_load_time
float32 resolution
uint32 width
uint32 height
geometry_msgs/msg/Pose origin
)RB"},
    {R"RB(nav_msgs/msg/OccupancyGrid)RB", R"RB(std_msgs/msg/Header header
nav_msgs/msg/MapMetaData info
int8[] data
)RB"},
    {R"RB(nav_msgs/msg/Odometry)RB", R"RB(std_msgs/msg/Header header
string child_frame_id
geometry_msgs/msg/PoseWithCovariance pose
geometry_msgs/msg/TwistWithCovariance twist
)RB"},
    {R"RB(nav_msgs/msg/Path)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/PoseStamped[] poses
)RB"},
    {R"RB(rcl_interfaces/msg/FloatingPointRange)RB", R"RB(float64 from_value
float64 to_value
float64 step
)RB"},
    {R"RB(rcl_interfaces/msg/IntegerRange)RB", R"RB(int64 from_value
int64 to_value
uint64 step
)RB"},
    {R"RB(rcl_interfaces/msg/ListParametersResult)RB", R"RB(string[] names
string[] prefixes
)RB"},
    {R"RB(rcl_interfaces/msg/Log)RB", R"RB(uint8 DEBUG=10
uint8 INFO=20
uint8 WARN=30
uint8 ERROR=40
uint8 FATAL=50
builtin_interfaces/msg/Time stamp
uint8 level
string name
string msg
string file
string function
uint32 line
)RB"},
    {R"RB(rcl_interfaces/msg/LoggerLevel)RB", R"RB(uint8 LOG_LEVEL_UNKNOWN=0
uint8 LOG_LEVEL_DEBUG=10
uint8 LOG_LEVEL_INFO=20
uint8 LOG_LEVEL_WARN=30
uint8 LOG_LEVEL_ERROR=40
uint8 LOG_LEVEL_FATAL=50
string name
uint32 level
)RB"},
    {R"RB(rcl_interfaces/msg/Parameter)RB", R"RB(string name
rcl_interfaces/msg/ParameterValue value
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterDescriptor)RB", R"RB(string name
uint8 type
string description
string additional_constraints
bool read_only
bool dynamic_typing
rcl_interfaces/msg/FloatingPointRange[<=1] floating_point_range
rcl_interfaces/msg/IntegerRange[<=1] integer_range
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterEvent)RB", R"RB(builtin_interfaces/msg/Time stamp
string node
rcl_interfaces/msg/Parameter[] new_parameters
rcl_interfaces/msg/Parameter[] changed_parameters
rcl_interfaces/msg/Parameter[] deleted_parameters
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterEventDescriptors)RB", R"RB(rcl_interfaces/msg/ParameterDescriptor[] new_parameters
rcl_interfaces/msg/ParameterDescriptor[] changed_parameters
rcl_interfaces/msg/ParameterDescriptor[] deleted_parameters
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterType)RB", R"RB(uint8 PARAMETER_NOT_SET=0
uint8 PARAMETER_BOOL=1
uint8 PARAMETER_INTEGER=2
uint8 PARAMETER_DOUBLE=3
uint8 PARAMETER_STRING=4
uint8 PARAMETER_BYTE_ARRAY=5
uint8 PARAMETER_BOOL_ARRAY=6
uint8 PARAMETER_INTEGER_ARRAY=7
uint8 PARAMETER_DOUBLE_ARRAY=8
uint8 PARAMETER_STRING_ARRAY=9
uint8 structure_needs_at_least_one_member
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterValue)RB", R"RB(uint8 type
bool bool_value
int64 integer_value
float64 double_value
string string_value
byte[] byte_array_value
bool[] bool_array_value
int64[] integer_array_value
float64[] double_array_value
string[] string_array_value
)RB"},
    {R"RB(rcl_interfaces/msg/SetLoggerLevelsResult)RB", R"RB(bool successful
string reason
)RB"},
    {R"RB(rcl_interfaces/msg/SetParametersResult)RB", R"RB(bool successful
string reason
)RB"},
    {R"RB(rmw_dds_common/msg/Gid)RB", R"RB(char[16] data
)RB"},
    {R"RB(rmw_dds_common/msg/NodeEntitiesInfo)RB", R"RB(string<=256 node_namespace
string<=256 node_name
rmw_dds_common/msg/Gid[] reader_gid_seq
rmw_dds_common/msg/Gid[] writer_gid_seq
)RB"},
    {R"RB(rmw_dds_common/msg/ParticipantEntitiesInfo)RB", R"RB(rmw_dds_common/msg/Gid gid
rmw_dds_common/msg/NodeEntitiesInfo[] node_entities_info_seq
)RB"},
    {R"RB(rosbag2_interfaces/msg/ReadSplitEvent)RB", R"RB(string closed_file
string opened_file
string node_name
)RB"},
    {R"RB(rosbag2_interfaces/msg/WriteSplitEvent)RB", R"RB(string closed_file
string opened_file
string node_name
)RB"},
    {R"RB(rosgraph_msgs/msg/Clock)RB", R"RB(builtin_interfaces/msg/Time clock
)RB"},
    {R"RB(sensor_msgs/msg/BatteryState)RB", R"RB(uint8 POWER_SUPPLY_STATUS_UNKNOWN=0
uint8 POWER_SUPPLY_STATUS_CHARGING=1
uint8 POWER_SUPPLY_STATUS_DISCHARGING=2
uint8 POWER_SUPPLY_STATUS_NOT_CHARGING=3
uint8 POWER_SUPPLY_STATUS_FULL=4
uint8 POWER_SUPPLY_HEALTH_UNKNOWN=0
uint8 POWER_SUPPLY_HEALTH_GOOD=1
uint8 POWER_SUPPLY_HEALTH_OVERHEAT=2
uint8 POWER_SUPPLY_HEALTH_DEAD=3
uint8 POWER_SUPPLY_HEALTH_OVERVOLTAGE=4
uint8 POWER_SUPPLY_HEALTH_UNSPEC_FAILURE=5
uint8 POWER_SUPPLY_HEALTH_COLD=6
uint8 POWER_SUPPLY_HEALTH_WATCHDOG_TIMER_EXPIRE=7
uint8 POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE=8
uint8 POWER_SUPPLY_TECHNOLOGY_UNKNOWN=0
uint8 POWER_SUPPLY_TECHNOLOGY_NIMH=1
uint8 POWER_SUPPLY_TECHNOLOGY_LION=2
uint8 POWER_SUPPLY_TECHNOLOGY_LIPO=3
uint8 POWER_SUPPLY_TECHNOLOGY_LIFE=4
uint8 POWER_SUPPLY_TECHNOLOGY_NICD=5
uint8 POWER_SUPPLY_TECHNOLOGY_LIMN=6
uint8 POWER_SUPPLY_TECHNOLOGY_TERNARY=7
uint8 POWER_SUPPLY_TECHNOLOGY_VRLA=8
std_msgs/msg/Header header
float32 voltage
float32 temperature
float32 current
float32 charge
float32 capacity
float32 design_capacity
float32 percentage
uint8 power_supply_status
uint8 power_supply_health
uint8 power_supply_technology
bool present
float32[] cell_voltage
float32[] cell_temperature
string location
string serial_number
)RB"},
    {R"RB(sensor_msgs/msg/CameraInfo)RB", R"RB(std_msgs/msg/Header header
uint32 height
uint32 width
string distortion_model
float64[] d
float64[9] k
float64[9] r
float64[12] p
uint32 binning_x
uint32 binning_y
sensor_msgs/msg/RegionOfInterest roi
)RB"},
    {R"RB(sensor_msgs/msg/ChannelFloat32)RB", R"RB(string name
float32[] values
)RB"},
    {R"RB(sensor_msgs/msg/CompressedImage)RB", R"RB(std_msgs/msg/Header header
string format
uint8[] data
)RB"},
    {R"RB(sensor_msgs/msg/FluidPressure)RB", R"RB(std_msgs/msg/Header header
float64 fluid_pressure
float64 variance
)RB"},
    {R"RB(sensor_msgs/msg/Illuminance)RB", R"RB(std_msgs/msg/Header header
float64 illuminance
float64 variance
)RB"},
    {R"RB(sensor_msgs/msg/Image)RB", R"RB(std_msgs/msg/Header header
uint32 height
uint32 width
string encoding
uint8 is_bigendian
uint32 step
uint8[] data
)RB"},
    {R"RB(sensor_msgs/msg/Imu)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Quaternion orientation
float64[9] orientation_covariance
geometry_msgs/msg/Vector3 angular_velocity
float64[9] angular_velocity_covariance
geometry_msgs/msg/Vector3 linear_acceleration
float64[9] linear_acceleration_covariance
)RB"},
    {R"RB(sensor_msgs/msg/JointState)RB", R"RB(std_msgs/msg/Header header
string[] name
float64[] position
float64[] velocity
float64[] effort
)RB"},
    {R"RB(sensor_msgs/msg/Joy)RB", R"RB(std_msgs/msg/Header header
float32[] axes
int32[] buttons
)RB"},
    {R"RB(sensor_msgs/msg/JoyFeedback)RB", R"RB(uint8 TYPE_LED=0
uint8 TYPE_RUMBLE=1
uint8 TYPE_BUZZER=2
uint8 type
uint8 id
float32 intensity
)RB"},
    {R"RB(sensor_msgs/msg/JoyFeedbackArray)RB", R"RB(sensor_msgs/msg/JoyFeedback[] array
)RB"},
    {R"RB(sensor_msgs/msg/LaserEcho)RB", R"RB(float32[] echoes
)RB"},
    {R"RB(sensor_msgs/msg/LaserScan)RB", R"RB(std_msgs/msg/Header header
float32 angle_min
float32 angle_max
float32 angle_increment
float32 time_increment
float32 scan_time
float32 range_min
float32 range_max
float32[] ranges
float32[] intensities
)RB"},
    {R"RB(sensor_msgs/msg/MagneticField)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Vector3 magnetic_field
float64[9] magnetic_field_covariance
)RB"},
    {R"RB(sensor_msgs/msg/MultiDOFJointState)RB", R"RB(std_msgs/msg/Header header
string[] joint_names
geometry_msgs/msg/Transform[] transforms
geometry_msgs/msg/Twist[] twist
geometry_msgs/msg/Wrench[] wrench
)RB"},
    {R"RB(sensor_msgs/msg/MultiEchoLaserScan)RB", R"RB(std_msgs/msg/Header header
float32 angle_min
float32 angle_max
float32 angle_increment
float32 time_increment
float32 scan_time
float32 range_min
float32 range_max
sensor_msgs/msg/LaserEcho[] ranges
sensor_msgs/msg/LaserEcho[] intensities
)RB"},
    {R"RB(sensor_msgs/msg/NavSatFix)RB", R"RB(uint8 COVARIANCE_TYPE_UNKNOWN=0
uint8 COVARIANCE_TYPE_APPROXIMATED=1
uint8 COVARIANCE_TYPE_DIAGONAL_KNOWN=2
uint8 COVARIANCE_TYPE_KNOWN=3
std_msgs/msg/Header header
sensor_msgs/msg/NavSatStatus status
float64 latitude
float64 longitude
float64 altitude
float64[9] position_covariance
uint8 position_covariance_type
)RB"},
    {R"RB(sensor_msgs/msg/NavSatStatus)RB", R"RB(int8 STATUS_UNKNOWN=-2
int8 STATUS_NO_FIX=-1
int8 STATUS_FIX=0
int8 STATUS_SBAS_FIX=1
int8 STATUS_GBAS_FIX=2
uint16 SERVICE_UNKNOWN=0
uint16 SERVICE_GPS=1
uint16 SERVICE_GLONASS=2
uint16 SERVICE_COMPASS=4
uint16 SERVICE_GALILEO=8
int8 status
uint16 service
)RB"},
    {R"RB(sensor_msgs/msg/PointCloud)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Point32[] points
sensor_msgs/msg/ChannelFloat32[] channels
)RB"},
    {R"RB(sensor_msgs/msg/PointCloud2)RB", R"RB(std_msgs/msg/Header header
uint32 height
uint32 width
sensor_msgs/msg/PointField[] fields
bool is_bigendian
uint32 point_step
uint32 row_step
uint8[] data
bool is_dense
)RB"},
    {R"RB(sensor_msgs/msg/PointField)RB", R"RB(uint8 INT8=1
uint8 UINT8=2
uint8 INT16=3
uint8 UINT16=4
uint8 INT32=5
uint8 UINT32=6
uint8 FLOAT32=7
uint8 FLOAT64=8
string name
uint32 offset
uint8 datatype
uint32 count
)RB"},
    {R"RB(sensor_msgs/msg/Range)RB", R"RB(uint8 ULTRASOUND=0
uint8 INFRARED=1
std_msgs/msg/Header header
uint8 radiation_type
float32 field_of_view
float32 min_range
float32 max_range
float32 range
float32 variance
)RB"},
    {R"RB(sensor_msgs/msg/RegionOfInterest)RB", R"RB(uint32 x_offset
uint32 y_offset
uint32 height
uint32 width
bool do_rectify
)RB"},
    {R"RB(sensor_msgs/msg/RelativeHumidity)RB", R"RB(std_msgs/msg/Header header
float64 relative_humidity
float64 variance
)RB"},
    {R"RB(sensor_msgs/msg/Temperature)RB", R"RB(std_msgs/msg/Header header
float64 temperature
float64 variance
)RB"},
    {R"RB(sensor_msgs/msg/TimeReference)RB", R"RB(std_msgs/msg/Header header
builtin_interfaces/msg/Time time_ref
string source
)RB"},
    {R"RB(service_msgs/msg/ServiceEventInfo)RB", R"RB(uint8 REQUEST_SENT=0
uint8 REQUEST_RECEIVED=1
uint8 RESPONSE_SENT=2
uint8 RESPONSE_RECEIVED=3
uint8 event_type
builtin_interfaces/msg/Time stamp
char[16] client_gid
int64 sequence_number
)RB"},
    {R"RB(shape_msgs/msg/Mesh)RB", R"RB(shape_msgs/msg/MeshTriangle[] triangles
geometry_msgs/msg/Point[] vertices
)RB"},
    {R"RB(shape_msgs/msg/MeshTriangle)RB", R"RB(uint32[3] vertex_indices
)RB"},
    {R"RB(shape_msgs/msg/Plane)RB", R"RB(float64[4] coef
)RB"},
    {R"RB(shape_msgs/msg/SolidPrimitive)RB", R"RB(uint8 BOX=1
uint8 SPHERE=2
uint8 CYLINDER=3
uint8 CONE=4
uint8 PRISM=5
uint8 BOX_X=0
uint8 BOX_Y=1
uint8 BOX_Z=2
uint8 SPHERE_RADIUS=0
uint8 CYLINDER_HEIGHT=0
uint8 CYLINDER_RADIUS=1
uint8 CONE_HEIGHT=0
uint8 CONE_RADIUS=1
uint8 PRISM_HEIGHT=0
uint8 type
float64[<=3] dimensions
geometry_msgs/msg/Polygon polygon
)RB"},
    {R"RB(statistics_msgs/msg/MetricsMessage)RB", R"RB(string measurement_source_name
string metrics_source
string unit
builtin_interfaces/msg/Time window_start
builtin_interfaces/msg/Time window_stop
statistics_msgs/msg/StatisticDataPoint[] statistics
)RB"},
    {R"RB(statistics_msgs/msg/StatisticDataPoint)RB", R"RB(uint8 data_type
float64 data
)RB"},
    {R"RB(statistics_msgs/msg/StatisticDataType)RB", R"RB(uint8 STATISTICS_DATA_TYPE_UNINITIALIZED=0
uint8 STATISTICS_DATA_TYPE_AVERAGE=1
uint8 STATISTICS_DATA_TYPE_MINIMUM=2
uint8 STATISTICS_DATA_TYPE_MAXIMUM=3
uint8 STATISTICS_DATA_TYPE_STDDEV=4
uint8 STATISTICS_DATA_TYPE_SAMPLE_COUNT=5
uint8 structure_needs_at_least_one_member
)RB"},
    {R"RB(std_msgs/msg/Bool)RB", R"RB(bool data
)RB"},
    {R"RB(std_msgs/msg/Byte)RB", R"RB(byte data
)RB"},
    {R"RB(std_msgs/msg/ByteMultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
byte[] data
)RB"},
    {R"RB(std_msgs/msg/Char)RB", R"RB(char data
)RB"},
    {R"RB(std_msgs/msg/ColorRGBA)RB", R"RB(float32 r
float32 g
float32 b
float32 a
)RB"},
    {R"RB(std_msgs/msg/Empty)RB", R"RB(uint8 structure_needs_at_least_one_member
)RB"},
    {R"RB(std_msgs/msg/Float32)RB", R"RB(float32 data
)RB"},
    {R"RB(std_msgs/msg/Float32MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
float32[] data
)RB"},
    {R"RB(std_msgs/msg/Float64)RB", R"RB(float64 data
)RB"},
    {R"RB(std_msgs/msg/Float64MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
float64[] data
)RB"},
    {R"RB(std_msgs/msg/Header)RB", R"RB(builtin_interfaces/msg/Time stamp
string frame_id
)RB"},
    {R"RB(std_msgs/msg/Int16)RB", R"RB(int16 data
)RB"},
    {R"RB(std_msgs/msg/Int16MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
int16[] data
)RB"},
    {R"RB(std_msgs/msg/Int32)RB", R"RB(int32 data
)RB"},
    {R"RB(std_msgs/msg/Int32MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
int32[] data
)RB"},
    {R"RB(std_msgs/msg/Int64)RB", R"RB(int64 data
)RB"},
    {R"RB(std_msgs/msg/Int64MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
int64[] data
)RB"},
    {R"RB(std_msgs/msg/Int8)RB", R"RB(int8 data
)RB"},
    {R"RB(std_msgs/msg/Int8MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
int8[] data
)RB"},
    {R"RB(std_msgs/msg/MultiArrayDimension)RB", R"RB(string label
uint32 size
uint32 stride
)RB"},
    {R"RB(std_msgs/msg/MultiArrayLayout)RB", R"RB(std_msgs/msg/MultiArrayDimension[] dim
uint32 data_offset
)RB"},
    {R"RB(std_msgs/msg/String)RB", R"RB(string data
)RB"},
    {R"RB(std_msgs/msg/UInt16)RB", R"RB(uint16 data
)RB"},
    {R"RB(std_msgs/msg/UInt16MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
uint16[] data
)RB"},
    {R"RB(std_msgs/msg/UInt32)RB", R"RB(uint32 data
)RB"},
    {R"RB(std_msgs/msg/UInt32MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
uint32[] data
)RB"},
    {R"RB(std_msgs/msg/UInt64)RB", R"RB(uint64 data
)RB"},
    {R"RB(std_msgs/msg/UInt64MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
uint64[] data
)RB"},
    {R"RB(std_msgs/msg/UInt8)RB", R"RB(uint8 data
)RB"},
    {R"RB(std_msgs/msg/UInt8MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
uint8[] data
)RB"},
    {R"RB(stereo_msgs/msg/DisparityImage)RB", R"RB(std_msgs/msg/Header header
sensor_msgs/msg/Image image
float32 f
float32 t
sensor_msgs/msg/RegionOfInterest valid_window
float32 min_disparity
float32 max_disparity
float32 delta_d
)RB"},
    {R"RB(tf2_msgs/msg/TF2Error)RB", R"RB(uint8 NO_ERROR=0
uint8 LOOKUP_ERROR=1
uint8 CONNECTIVITY_ERROR=2
uint8 EXTRAPOLATION_ERROR=3
uint8 INVALID_ARGUMENT_ERROR=4
uint8 TIMEOUT_ERROR=5
uint8 TRANSFORM_ERROR=6
uint8 error
string error_string
)RB"},
    {R"RB(tf2_msgs/msg/TFMessage)RB", R"RB(geometry_msgs/msg/TransformStamped[] transforms
)RB"},
    {R"RB(trajectory_msgs/msg/JointTrajectory)RB", R"RB(std_msgs/msg/Header header
string[] joint_names
trajectory_msgs/msg/JointTrajectoryPoint[] points
)RB"},
    {R"RB(trajectory_msgs/msg/JointTrajectoryPoint)RB", R"RB(float64[] positions
float64[] velocities
float64[] accelerations
float64[] effort
builtin_interfaces/msg/Duration time_from_start
)RB"},
    {R"RB(trajectory_msgs/msg/MultiDOFJointTrajectory)RB", R"RB(std_msgs/msg/Header header
string[] joint_names
trajectory_msgs/msg/MultiDOFJointTrajectoryPoint[] points
)RB"},
    {R"RB(trajectory_msgs/msg/MultiDOFJointTrajectoryPoint)RB", R"RB(geometry_msgs/msg/Transform[] transforms
geometry_msgs/msg/Twist[] velocities
geometry_msgs/msg/Twist[] accelerations
builtin_interfaces/msg/Duration time_from_start
)RB"},
    {R"RB(type_description_interfaces/msg/Field)RB", R"RB(string name
type_description_interfaces/msg/FieldType type
string default_value
)RB"},
    {R"RB(type_description_interfaces/msg/FieldType)RB", R"RB(uint8 FIELD_TYPE_NOT_SET=0
uint8 FIELD_TYPE_NESTED_TYPE=1
uint8 FIELD_TYPE_INT8=2
uint8 FIELD_TYPE_UINT8=3
uint8 FIELD_TYPE_INT16=4
uint8 FIELD_TYPE_UINT16=5
uint8 FIELD_TYPE_INT32=6
uint8 FIELD_TYPE_UINT32=7
uint8 FIELD_TYPE_INT64=8
uint8 FIELD_TYPE_UINT64=9
uint8 FIELD_TYPE_FLOAT=10
uint8 FIELD_TYPE_DOUBLE=11
uint8 FIELD_TYPE_LONG_DOUBLE=12
uint8 FIELD_TYPE_CHAR=13
uint8 FIELD_TYPE_WCHAR=14
uint8 FIELD_TYPE_BOOLEAN=15
uint8 FIELD_TYPE_BYTE=16
uint8 FIELD_TYPE_STRING=17
uint8 FIELD_TYPE_WSTRING=18
uint8 FIELD_TYPE_FIXED_STRING=19
uint8 FIELD_TYPE_FIXED_WSTRING=20
uint8 FIELD_TYPE_BOUNDED_STRING=21
uint8 FIELD_TYPE_BOUNDED_WSTRING=22
uint8 FIELD_TYPE_NESTED_TYPE_ARRAY=49
uint8 FIELD_TYPE_INT8_ARRAY=50
uint8 FIELD_TYPE_UINT8_ARRAY=51
uint8 FIELD_TYPE_INT16_ARRAY=52
uint8 FIELD_TYPE_UINT16_ARRAY=53
uint8 FIELD_TYPE_INT32_ARRAY=54
uint8 FIELD_TYPE_UINT32_ARRAY=55
uint8 FIELD_TYPE_INT64_ARRAY=56
uint8 FIELD_TYPE_UINT64_ARRAY=57
uint8 FIELD_TYPE_FLOAT_ARRAY=58
uint8 FIELD_TYPE_DOUBLE_ARRAY=59
uint8 FIELD_TYPE_LONG_DOUBLE_ARRAY=60
uint8 FIELD_TYPE_CHAR_ARRAY=61
uint8 FIELD_TYPE_WCHAR_ARRAY=62
uint8 FIELD_TYPE_BOOLEAN_ARRAY=63
uint8 FIELD_TYPE_BYTE_ARRAY=64
uint8 FIELD_TYPE_STRING_ARRAY=65
uint8 FIELD_TYPE_WSTRING_ARRAY=66
uint8 FIELD_TYPE_FIXED_STRING_ARRAY=67
uint8 FIELD_TYPE_FIXED_WSTRING_ARRAY=68
uint8 FIELD_TYPE_BOUNDED_STRING_ARRAY=69
uint8 FIELD_TYPE_BOUNDED_WSTRING_ARRAY=70
uint8 FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE=97
uint8 FIELD_TYPE_INT8_BOUNDED_SEQUENCE=98
uint8 FIELD_TYPE_UINT8_BOUNDED_SEQUENCE=99
uint8 FIELD_TYPE_INT16_BOUNDED_SEQUENCE=100
uint8 FIELD_TYPE_UINT16_BOUNDED_SEQUENCE=101
uint8 FIELD_TYPE_INT32_BOUNDED_SEQUENCE=102
uint8 FIELD_TYPE_UINT32_BOUNDED_SEQUENCE=103
uint8 FIELD_TYPE_INT64_BOUNDED_SEQUENCE=104
uint8 FIELD_TYPE_UINT64_BOUNDED_SEQUENCE=105
uint8 FIELD_TYPE_FLOAT_BOUNDED_SEQUENCE=106
uint8 FIELD_TYPE_DOUBLE_BOUNDED_SEQUENCE=107
uint8 FIELD_TYPE_LONG_DOUBLE_BOUNDED_SEQUENCE=108
uint8 FIELD_TYPE_CHAR_BOUNDED_SEQUENCE=109
uint8 FIELD_TYPE_WCHAR_BOUNDED_SEQUENCE=110
uint8 FIELD_TYPE_BOOLEAN_BOUNDED_SEQUENCE=111
uint8 FIELD_TYPE_BYTE_BOUNDED_SEQUENCE=112
uint8 FIELD_TYPE_STRING_BOUNDED_SEQUENCE=113
uint8 FIELD_TYPE_WSTRING_BOUNDED_SEQUENCE=114
uint8 FIELD_TYPE_FIXED_STRING_BOUNDED_SEQUENCE=115
uint8 FIELD_TYPE_FIXED_WSTRING_BOUNDED_SEQUENCE=116
uint8 FIELD_TYPE_BOUNDED_STRING_BOUNDED_SEQUENCE=117
uint8 FIELD_TYPE_BOUNDED_WSTRING_BOUNDED_SEQUENCE=118
uint8 FIELD_TYPE_NESTED_TYPE_UNBOUNDED_SEQUENCE=145
uint8 FIELD_TYPE_INT8_UNBOUNDED_SEQUENCE=146
uint8 FIELD_TYPE_UINT8_UNBOUNDED_SEQUENCE=147
uint8 FIELD_TYPE_INT16_UNBOUNDED_SEQUENCE=148
uint8 FIELD_TYPE_UINT16_UNBOUNDED_SEQUENCE=149
uint8 FIELD_TYPE_INT32_UNBOUNDED_SEQUENCE=150
uint8 FIELD_TYPE_UINT32_UNBOUNDED_SEQUENCE=151
uint8 FIELD_TYPE_INT64_UNBOUNDED_SEQUENCE=152
uint8 FIELD_TYPE_UINT64_UNBOUNDED_SEQUENCE=153
uint8 FIELD_TYPE_FLOAT_UNBOUNDED_SEQUENCE=154
uint8 FIELD_TYPE_DOUBLE_UNBOUNDED_SEQUENCE=155
uint8 FIELD_TYPE_LONG_DOUBLE_UNBOUNDED_SEQUENCE=156
uint8 FIELD_TYPE_CHAR_UNBOUNDED_SEQUENCE=157
uint8 FIELD_TYPE_WCHAR_UNBOUNDED_SEQUENCE=158
uint8 FIELD_TYPE_BOOLEAN_UNBOUNDED_SEQUENCE=159
uint8 FIELD_TYPE_BYTE_UNBOUNDED_SEQUENCE=160
uint8 FIELD_TYPE_STRING_UNBOUNDED_SEQUENCE=161
uint8 FIELD_TYPE_WSTRING_UNBOUNDED_SEQUENCE=162
uint8 FIELD_TYPE_FIXED_STRING_UNBOUNDED_SEQUENCE=163
uint8 FIELD_TYPE_FIXED_WSTRING_UNBOUNDED_SEQUENCE=164
uint8 FIELD_TYPE_BOUNDED_STRING_UNBOUNDED_SEQUENCE=165
uint8 FIELD_TYPE_BOUNDED_WSTRING_UNBOUNDED_SEQUENCE=166
uint8 type_id
uint64 capacity
uint64 string_capacity
string<=255 nested_type_name
)RB"},
    {R"RB(type_description_interfaces/msg/IndividualTypeDescription)RB", R"RB(string<=255 type_name
type_description_interfaces/msg/Field[] fields
)RB"},
    {R"RB(type_description_interfaces/msg/KeyValue)RB", R"RB(string key
string value
)RB"},
    {R"RB(type_description_interfaces/msg/TypeDescription)RB", R"RB(type_description_interfaces/msg/IndividualTypeDescription type_description
type_description_interfaces/msg/IndividualTypeDescription[] referenced_type_descriptions
)RB"},
    {R"RB(type_description_interfaces/msg/TypeSource)RB", R"RB(string type_name
string encoding
string raw_file_contents
)RB"},
    {R"RB(unique_identifier_msgs/msg/UUID)RB", R"RB(uint8[16] uuid
)RB"},
    {R"RB(visualization_msgs/msg/ImageMarker)RB", R"RB(int32 CIRCLE=0
int32 LINE_STRIP=1
int32 LINE_LIST=2
int32 POLYGON=3
int32 POINTS=4
int32 ADD=0
int32 REMOVE=1
std_msgs/msg/Header header
string ns
int32 id
int32 type
int32 action
geometry_msgs/msg/Point position
float32 scale
std_msgs/msg/ColorRGBA outline_color
uint8 filled
std_msgs/msg/ColorRGBA fill_color
builtin_interfaces/msg/Duration lifetime
geometry_msgs/msg/Point[] points
std_msgs/msg/ColorRGBA[] outline_colors
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarker)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Pose pose
string name
string description
float32 scale
visualization_msgs/msg/MenuEntry[] menu_entries
visualization_msgs/msg/InteractiveMarkerControl[] controls
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerControl)RB", R"RB(uint8 INHERIT=0
uint8 FIXED=1
uint8 VIEW_FACING=2
uint8 NONE=0
uint8 MENU=1
uint8 BUTTON=2
uint8 MOVE_AXIS=3
uint8 MOVE_PLANE=4
uint8 ROTATE_AXIS=5
uint8 MOVE_ROTATE=6
uint8 MOVE_3D=7
uint8 ROTATE_3D=8
uint8 MOVE_ROTATE_3D=9
string name
geometry_msgs/msg/Quaternion orientation
uint8 orientation_mode
uint8 interaction_mode
bool always_visible
visualization_msgs/msg/Marker[] markers
bool independent_marker_orientation
string description
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerFeedback)RB", R"RB(uint8 KEEP_ALIVE=0
uint8 POSE_UPDATE=1
uint8 MENU_SELECT=2
uint8 BUTTON_CLICK=3
uint8 MOUSE_DOWN=4
uint8 MOUSE_UP=5
std_msgs/msg/Header header
string client_id
string marker_name
string control_name
uint8 event_type
geometry_msgs/msg/Pose pose
uint32 menu_entry_id
geometry_msgs/msg/Point mouse_point
bool mouse_point_valid
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerInit)RB", R"RB(string server_id
uint64 seq_num
visualization_msgs/msg/InteractiveMarker[] markers
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerPose)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Pose pose
string name
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerUpdate)RB", R"RB(uint8 KEEP_ALIVE=0
uint8 UPDATE=1
string server_id
uint64 seq_num
uint8 type
visualization_msgs/msg/InteractiveMarker[] markers
visualization_msgs/msg/InteractiveMarkerPose[] poses
string[] erases
)RB"},
    {R"RB(visualization_msgs/msg/Marker)RB", R"RB(int32 ARROW=0
int32 CUBE=1
int32 SPHERE=2
int32 CYLINDER=3
int32 LINE_STRIP=4
int32 LINE_LIST=5
int32 CUBE_LIST=6
int32 SPHERE_LIST=7
int32 POINTS=8
int32 TEXT_VIEW_FACING=9
int32 MESH_RESOURCE=10
int32 TRIANGLE_LIST=11
int32 ARROW_STRIP=12
int32 ADD=0
int32 MODIFY=0
int32 DELETE=2
int32 DELETEALL=3
std_msgs/msg/Header header
string ns
int32 id
int32 type
int32 action
geometry_msgs/msg/Pose pose
geometry_msgs/msg/Vector3 scale
std_msgs/msg/ColorRGBA color
builtin_interfaces/msg/Duration lifetime
bool frame_locked
geometry_msgs/msg/Point[] points
std_msgs/msg/ColorRGBA[] colors
string texture_resource
sensor_msgs/msg/CompressedImage texture
visualization_msgs/msg/UVCoordinate[] uv_coordinates
string text
string mesh_resource
visualization_msgs/msg/MeshFile mesh_file
bool mesh_use_embedded_materials
)RB"},
    {R"RB(visualization_msgs/msg/MarkerArray)RB", R"RB(visualization_msgs/msg/Marker[] markers
)RB"},
    {R"RB(visualization_msgs/msg/MenuEntry)RB", R"RB(uint8 FEEDBACK=0
uint8 ROSRUN=1
uint8 ROSLAUNCH=2
uint32 id
uint32 parent_id
string title
string command
uint8 command_type
)RB"},
    {R"RB(visualization_msgs/msg/MeshFile)RB", R"RB(string filename
uint8[] data
)RB"},
    {R"RB(visualization_msgs/msg/UVCoordinate)RB", R"RB(float32 u
float32 v
)RB"},
};

const GeneratedTypeDefinition kRos2KiltedTypes[] = {
    {R"RB(action_msgs/msg/GoalInfo)RB", R"RB(unique_identifier_msgs/msg/UUID goal_id
builtin_interfaces/msg/Time stamp
)RB"},
    {R"RB(action_msgs/msg/GoalStatus)RB", R"RB(int8 STATUS_UNKNOWN=0
int8 STATUS_ACCEPTED=1
int8 STATUS_EXECUTING=2
int8 STATUS_CANCELING=3
int8 STATUS_SUCCEEDED=4
int8 STATUS_CANCELED=5
int8 STATUS_ABORTED=6
action_msgs/msg/GoalInfo goal_info
int8 status
)RB"},
    {R"RB(action_msgs/msg/GoalStatusArray)RB", R"RB(action_msgs/msg/GoalStatus[] status_list
)RB"},
    {R"RB(actionlib_msgs/msg/GoalID)RB", R"RB(builtin_interfaces/msg/Time stamp
string id
)RB"},
    {R"RB(actionlib_msgs/msg/GoalStatus)RB", R"RB(uint8 PENDING=0
uint8 ACTIVE=1
uint8 PREEMPTED=2
uint8 SUCCEEDED=3
uint8 ABORTED=4
uint8 REJECTED=5
uint8 PREEMPTING=6
uint8 RECALLING=7
uint8 RECALLED=8
uint8 LOST=9
actionlib_msgs/msg/GoalID goal_id
uint8 status
string text
)RB"},
    {R"RB(actionlib_msgs/msg/GoalStatusArray)RB", R"RB(std_msgs/msg/Header header
actionlib_msgs/msg/GoalStatus[] status_list
)RB"},
    {R"RB(builtin_interfaces/msg/Duration)RB", R"RB(int32 sec
uint32 nanosec
)RB"},
    {R"RB(builtin_interfaces/msg/Time)RB", R"RB(int32 sec
uint32 nanosec
)RB"},
    {R"RB(diagnostic_msgs/msg/DiagnosticArray)RB", R"RB(std_msgs/msg/Header header
diagnostic_msgs/msg/DiagnosticStatus[] status
)RB"},
    {R"RB(diagnostic_msgs/msg/DiagnosticStatus)RB", R"RB(byte OK=0
byte WARN=1
byte ERROR=2
byte STALE=3
byte level
string name
string message
string hardware_id
diagnostic_msgs/msg/KeyValue[] values
)RB"},
    {R"RB(diagnostic_msgs/msg/KeyValue)RB", R"RB(string key
string value
)RB"},
    {R"RB(geometry_msgs/msg/Accel)RB", R"RB(geometry_msgs/msg/Vector3 linear
geometry_msgs/msg/Vector3 angular
)RB"},
    {R"RB(geometry_msgs/msg/AccelStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Accel accel
)RB"},
    {R"RB(geometry_msgs/msg/AccelWithCovariance)RB", R"RB(geometry_msgs/msg/Accel accel
float64[36] covariance
)RB"},
    {R"RB(geometry_msgs/msg/AccelWithCovarianceStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/AccelWithCovariance accel
)RB"},
    {R"RB(geometry_msgs/msg/Inertia)RB", R"RB(float64 m
geometry_msgs/msg/Vector3 com
float64 ixx
float64 ixy
float64 ixz
float64 iyy
float64 iyz
float64 izz
)RB"},
    {R"RB(geometry_msgs/msg/InertiaStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Inertia inertia
)RB"},
    {R"RB(geometry_msgs/msg/Point)RB", R"RB(float64 x
float64 y
float64 z
)RB"},
    {R"RB(geometry_msgs/msg/Point32)RB", R"RB(float32 x
float32 y
float32 z
)RB"},
    {R"RB(geometry_msgs/msg/PointStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Point point
)RB"},
    {R"RB(geometry_msgs/msg/Polygon)RB", R"RB(geometry_msgs/msg/Point32[] points
)RB"},
    {R"RB(geometry_msgs/msg/PolygonInstance)RB", R"RB(geometry_msgs/msg/Polygon polygon
int64 id
)RB"},
    {R"RB(geometry_msgs/msg/PolygonInstanceStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/PolygonInstance polygon
)RB"},
    {R"RB(geometry_msgs/msg/PolygonStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Polygon polygon
)RB"},
    {R"RB(geometry_msgs/msg/Pose)RB", R"RB(geometry_msgs/msg/Point position
geometry_msgs/msg/Quaternion orientation
)RB"},
    {R"RB(geometry_msgs/msg/Pose2D)RB", R"RB(float64 x
float64 y
float64 theta
)RB"},
    {R"RB(geometry_msgs/msg/PoseArray)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Pose[] poses
)RB"},
    {R"RB(geometry_msgs/msg/PoseStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Pose pose
)RB"},
    {R"RB(geometry_msgs/msg/PoseWithCovariance)RB", R"RB(geometry_msgs/msg/Pose pose
float64[36] covariance
)RB"},
    {R"RB(geometry_msgs/msg/PoseWithCovarianceStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/PoseWithCovariance pose
)RB"},
    {R"RB(geometry_msgs/msg/Quaternion)RB", R"RB(float64 x
float64 y
float64 z
float64 w
)RB"},
    {R"RB(geometry_msgs/msg/QuaternionStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Quaternion quaternion
)RB"},
    {R"RB(geometry_msgs/msg/Transform)RB", R"RB(geometry_msgs/msg/Vector3 translation
geometry_msgs/msg/Quaternion rotation
)RB"},
    {R"RB(geometry_msgs/msg/TransformStamped)RB", R"RB(std_msgs/msg/Header header
string child_frame_id
geometry_msgs/msg/Transform transform
)RB"},
    {R"RB(geometry_msgs/msg/Twist)RB", R"RB(geometry_msgs/msg/Vector3 linear
geometry_msgs/msg/Vector3 angular
)RB"},
    {R"RB(geometry_msgs/msg/TwistStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Twist twist
)RB"},
    {R"RB(geometry_msgs/msg/TwistWithCovariance)RB", R"RB(geometry_msgs/msg/Twist twist
float64[36] covariance
)RB"},
    {R"RB(geometry_msgs/msg/TwistWithCovarianceStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/TwistWithCovariance twist
)RB"},
    {R"RB(geometry_msgs/msg/Vector3)RB", R"RB(float64 x
float64 y
float64 z
)RB"},
    {R"RB(geometry_msgs/msg/Vector3Stamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Vector3 vector
)RB"},
    {R"RB(geometry_msgs/msg/VelocityStamped)RB", R"RB(std_msgs/msg/Header header
string body_frame_id
string reference_frame_id
geometry_msgs/msg/Twist velocity
)RB"},
    {R"RB(geometry_msgs/msg/Wrench)RB", R"RB(geometry_msgs/msg/Vector3 force
geometry_msgs/msg/Vector3 torque
)RB"},
    {R"RB(geometry_msgs/msg/WrenchStamped)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Wrench wrench
)RB"},
    {R"RB(lifecycle_msgs/msg/State)RB", R"RB(uint8 PRIMARY_STATE_UNKNOWN=0
uint8 PRIMARY_STATE_UNCONFIGURED=1
uint8 PRIMARY_STATE_INACTIVE=2
uint8 PRIMARY_STATE_ACTIVE=3
uint8 PRIMARY_STATE_FINALIZED=4
uint8 TRANSITION_STATE_CONFIGURING=10
uint8 TRANSITION_STATE_CLEANINGUP=11
uint8 TRANSITION_STATE_SHUTTINGDOWN=12
uint8 TRANSITION_STATE_ACTIVATING=13
uint8 TRANSITION_STATE_DEACTIVATING=14
uint8 TRANSITION_STATE_ERRORPROCESSING=15
uint8 id
string label
)RB"},
    {R"RB(lifecycle_msgs/msg/Transition)RB", R"RB(uint8 TRANSITION_CREATE=0
uint8 TRANSITION_CONFIGURE=1
uint8 TRANSITION_CLEANUP=2
uint8 TRANSITION_ACTIVATE=3
uint8 TRANSITION_DEACTIVATE=4
uint8 TRANSITION_UNCONFIGURED_SHUTDOWN=5
uint8 TRANSITION_INACTIVE_SHUTDOWN=6
uint8 TRANSITION_ACTIVE_SHUTDOWN=7
uint8 TRANSITION_DESTROY=8
uint8 TRANSITION_ON_CONFIGURE_SUCCESS=10
uint8 TRANSITION_ON_CONFIGURE_FAILURE=11
uint8 TRANSITION_ON_CONFIGURE_ERROR=12
uint8 TRANSITION_ON_CLEANUP_SUCCESS=20
uint8 TRANSITION_ON_CLEANUP_FAILURE=21
uint8 TRANSITION_ON_CLEANUP_ERROR=22
uint8 TRANSITION_ON_ACTIVATE_SUCCESS=30
uint8 TRANSITION_ON_ACTIVATE_FAILURE=31
uint8 TRANSITION_ON_ACTIVATE_ERROR=32
uint8 TRANSITION_ON_DEACTIVATE_SUCCESS=40
uint8 TRANSITION_ON_DEACTIVATE_FAILURE=41
uint8 TRANSITION_ON_DEACTIVATE_ERROR=42
uint8 TRANSITION_ON_SHUTDOWN_SUCCESS=50
uint8 TRANSITION_ON_SHUTDOWN_FAILURE=51
uint8 TRANSITION_ON_SHUTDOWN_ERROR=52
uint8 TRANSITION_ON_ERROR_SUCCESS=60
uint8 TRANSITION_ON_ERROR_FAILURE=61
uint8 TRANSITION_ON_ERROR_ERROR=62
uint8 TRANSITION_CALLBACK_SUCCESS=97
uint8 TRANSITION_CALLBACK_FAILURE=98
uint8 TRANSITION_CALLBACK_ERROR=99
uint8 id
string label
)RB"},
    {R"RB(lifecycle_msgs/msg/TransitionDescription)RB", R"RB(lifecycle_msgs/msg/Transition transition
lifecycle_msgs/msg/State start_state
lifecycle_msgs/msg/State goal_state
)RB"},
    {R"RB(lifecycle_msgs/msg/TransitionEvent)RB", R"RB(uint64 timestamp
lifecycle_msgs/msg/Transition transition
lifecycle_msgs/msg/State start_state
lifecycle_msgs/msg/State goal_state
)RB"},
    {R"RB(nav_msgs/msg/Goals)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/PoseStamped[] goals
)RB"},
    {R"RB(nav_msgs/msg/GridCells)RB", R"RB(std_msgs/msg/Header header
float32 cell_width
float32 cell_height
geometry_msgs/msg/Point[] cells
)RB"},
    {R"RB(nav_msgs/msg/MapMetaData)RB", R"RB(builtin_interfaces/msg/Time map_load_time
float32 resolution
uint32 width
uint32 height
geometry_msgs/msg/Pose origin
)RB"},
    {R"RB(nav_msgs/msg/OccupancyGrid)RB", R"RB(std_msgs/msg/Header header
nav_msgs/msg/MapMetaData info
int8[] data
)RB"},
    {R"RB(nav_msgs/msg/Odometry)RB", R"RB(std_msgs/msg/Header header
string child_frame_id
geometry_msgs/msg/PoseWithCovariance pose
geometry_msgs/msg/TwistWithCovariance twist
)RB"},
    {R"RB(nav_msgs/msg/Path)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/PoseStamped[] poses
)RB"},
    {R"RB(rcl_interfaces/msg/FloatingPointRange)RB", R"RB(float64 from_value
float64 to_value
float64 step
)RB"},
    {R"RB(rcl_interfaces/msg/IntegerRange)RB", R"RB(int64 from_value
int64 to_value
uint64 step
)RB"},
    {R"RB(rcl_interfaces/msg/ListParametersResult)RB", R"RB(string[] names
string[] prefixes
)RB"},
    {R"RB(rcl_interfaces/msg/Log)RB", R"RB(uint8 DEBUG=10
uint8 INFO=20
uint8 WARN=30
uint8 ERROR=40
uint8 FATAL=50
builtin_interfaces/msg/Time stamp
uint8 level
string name
string msg
string file
string function
uint32 line
)RB"},
    {R"RB(rcl_interfaces/msg/LoggerLevel)RB", R"RB(uint8 LOG_LEVEL_UNKNOWN=0
uint8 LOG_LEVEL_DEBUG=10
uint8 LOG_LEVEL_INFO=20
uint8 LOG_LEVEL_WARN=30
uint8 LOG_LEVEL_ERROR=40
uint8 LOG_LEVEL_FATAL=50
string name
uint32 level
)RB"},
    {R"RB(rcl_interfaces/msg/Parameter)RB", R"RB(string name
rcl_interfaces/msg/ParameterValue value
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterDescriptor)RB", R"RB(string name
uint8 type
string description
string additional_constraints
bool read_only
bool dynamic_typing
rcl_interfaces/msg/FloatingPointRange[<=1] floating_point_range
rcl_interfaces/msg/IntegerRange[<=1] integer_range
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterEvent)RB", R"RB(builtin_interfaces/msg/Time stamp
string node
rcl_interfaces/msg/Parameter[] new_parameters
rcl_interfaces/msg/Parameter[] changed_parameters
rcl_interfaces/msg/Parameter[] deleted_parameters
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterEventDescriptors)RB", R"RB(rcl_interfaces/msg/ParameterDescriptor[] new_parameters
rcl_interfaces/msg/ParameterDescriptor[] changed_parameters
rcl_interfaces/msg/ParameterDescriptor[] deleted_parameters
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterType)RB", R"RB(uint8 PARAMETER_NOT_SET=0
uint8 PARAMETER_BOOL=1
uint8 PARAMETER_INTEGER=2
uint8 PARAMETER_DOUBLE=3
uint8 PARAMETER_STRING=4
uint8 PARAMETER_BYTE_ARRAY=5
uint8 PARAMETER_BOOL_ARRAY=6
uint8 PARAMETER_INTEGER_ARRAY=7
uint8 PARAMETER_DOUBLE_ARRAY=8
uint8 PARAMETER_STRING_ARRAY=9
uint8 structure_needs_at_least_one_member
)RB"},
    {R"RB(rcl_interfaces/msg/ParameterValue)RB", R"RB(uint8 type
bool bool_value
int64 integer_value
float64 double_value
string string_value
byte[] byte_array_value
bool[] bool_array_value
int64[] integer_array_value
float64[] double_array_value
string[] string_array_value
)RB"},
    {R"RB(rcl_interfaces/msg/SetLoggerLevelsResult)RB", R"RB(bool successful
string reason
)RB"},
    {R"RB(rcl_interfaces/msg/SetParametersResult)RB", R"RB(bool successful
string reason
)RB"},
    {R"RB(rmw_dds_common/msg/Gid)RB", R"RB(char[16] data
)RB"},
    {R"RB(rmw_dds_common/msg/NodeEntitiesInfo)RB", R"RB(string<=256 node_namespace
string<=256 node_name
rmw_dds_common/msg/Gid[] reader_gid_seq
rmw_dds_common/msg/Gid[] writer_gid_seq
)RB"},
    {R"RB(rmw_dds_common/msg/ParticipantEntitiesInfo)RB", R"RB(rmw_dds_common/msg/Gid gid
rmw_dds_common/msg/NodeEntitiesInfo[] node_entities_info_seq
)RB"},
    {R"RB(rosbag2_interfaces/msg/ReadSplitEvent)RB", R"RB(string closed_file
string opened_file
string node_name
)RB"},
    {R"RB(rosbag2_interfaces/msg/WriteSplitEvent)RB", R"RB(string closed_file
string opened_file
string node_name
)RB"},
    {R"RB(rosgraph_msgs/msg/Clock)RB", R"RB(builtin_interfaces/msg/Time clock
)RB"},
    {R"RB(sensor_msgs/msg/BatteryState)RB", R"RB(uint8 POWER_SUPPLY_STATUS_UNKNOWN=0
uint8 POWER_SUPPLY_STATUS_CHARGING=1
uint8 POWER_SUPPLY_STATUS_DISCHARGING=2
uint8 POWER_SUPPLY_STATUS_NOT_CHARGING=3
uint8 POWER_SUPPLY_STATUS_FULL=4
uint8 POWER_SUPPLY_HEALTH_UNKNOWN=0
uint8 POWER_SUPPLY_HEALTH_GOOD=1
uint8 POWER_SUPPLY_HEALTH_OVERHEAT=2
uint8 POWER_SUPPLY_HEALTH_DEAD=3
uint8 POWER_SUPPLY_HEALTH_OVERVOLTAGE=4
uint8 POWER_SUPPLY_HEALTH_UNSPEC_FAILURE=5
uint8 POWER_SUPPLY_HEALTH_COLD=6
uint8 POWER_SUPPLY_HEALTH_WATCHDOG_TIMER_EXPIRE=7
uint8 POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE=8
uint8 POWER_SUPPLY_TECHNOLOGY_UNKNOWN=0
uint8 POWER_SUPPLY_TECHNOLOGY_NIMH=1
uint8 POWER_SUPPLY_TECHNOLOGY_LION=2
uint8 POWER_SUPPLY_TECHNOLOGY_LIPO=3
uint8 POWER_SUPPLY_TECHNOLOGY_LIFE=4
uint8 POWER_SUPPLY_TECHNOLOGY_NICD=5
uint8 POWER_SUPPLY_TECHNOLOGY_LIMN=6
uint8 POWER_SUPPLY_TECHNOLOGY_TERNARY=7
uint8 POWER_SUPPLY_TECHNOLOGY_VRLA=8
std_msgs/msg/Header header
float32 voltage
float32 temperature
float32 current
float32 charge
float32 capacity
float32 design_capacity
float32 percentage
uint8 power_supply_status
uint8 power_supply_health
uint8 power_supply_technology
bool present
float32[] cell_voltage
float32[] cell_temperature
string location
string serial_number
)RB"},
    {R"RB(sensor_msgs/msg/CameraInfo)RB", R"RB(std_msgs/msg/Header header
uint32 height
uint32 width
string distortion_model
float64[] d
float64[9] k
float64[9] r
float64[12] p
uint32 binning_x
uint32 binning_y
sensor_msgs/msg/RegionOfInterest roi
)RB"},
    {R"RB(sensor_msgs/msg/ChannelFloat32)RB", R"RB(string name
float32[] values
)RB"},
    {R"RB(sensor_msgs/msg/CompressedImage)RB", R"RB(std_msgs/msg/Header header
string format
uint8[] data
)RB"},
    {R"RB(sensor_msgs/msg/FluidPressure)RB", R"RB(std_msgs/msg/Header header
float64 fluid_pressure
float64 variance
)RB"},
    {R"RB(sensor_msgs/msg/Illuminance)RB", R"RB(std_msgs/msg/Header header
float64 illuminance
float64 variance
)RB"},
    {R"RB(sensor_msgs/msg/Image)RB", R"RB(std_msgs/msg/Header header
uint32 height
uint32 width
string encoding
uint8 is_bigendian
uint32 step
uint8[] data
)RB"},
    {R"RB(sensor_msgs/msg/Imu)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Quaternion orientation
float64[9] orientation_covariance
geometry_msgs/msg/Vector3 angular_velocity
float64[9] angular_velocity_covariance
geometry_msgs/msg/Vector3 linear_acceleration
float64[9] linear_acceleration_covariance
)RB"},
    {R"RB(sensor_msgs/msg/JointState)RB", R"RB(std_msgs/msg/Header header
string[] name
float64[] position
float64[] velocity
float64[] effort
)RB"},
    {R"RB(sensor_msgs/msg/Joy)RB", R"RB(std_msgs/msg/Header header
float32[] axes
int32[] buttons
)RB"},
    {R"RB(sensor_msgs/msg/JoyFeedback)RB", R"RB(uint8 TYPE_LED=0
uint8 TYPE_RUMBLE=1
uint8 TYPE_BUZZER=2
uint8 type
uint8 id
float32 intensity
)RB"},
    {R"RB(sensor_msgs/msg/JoyFeedbackArray)RB", R"RB(sensor_msgs/msg/JoyFeedback[] array
)RB"},
    {R"RB(sensor_msgs/msg/LaserEcho)RB", R"RB(float32[] echoes
)RB"},
    {R"RB(sensor_msgs/msg/LaserScan)RB", R"RB(std_msgs/msg/Header header
float32 angle_min
float32 angle_max
float32 angle_increment
float32 time_increment
float32 scan_time
float32 range_min
float32 range_max
float32[] ranges
float32[] intensities
)RB"},
    {R"RB(sensor_msgs/msg/MagneticField)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Vector3 magnetic_field
float64[9] magnetic_field_covariance
)RB"},
    {R"RB(sensor_msgs/msg/MultiDOFJointState)RB", R"RB(std_msgs/msg/Header header
string[] joint_names
geometry_msgs/msg/Transform[] transforms
geometry_msgs/msg/Twist[] twist
geometry_msgs/msg/Wrench[] wrench
)RB"},
    {R"RB(sensor_msgs/msg/MultiEchoLaserScan)RB", R"RB(std_msgs/msg/Header header
float32 angle_min
float32 angle_max
float32 angle_increment
float32 time_increment
float32 scan_time
float32 range_min
float32 range_max
sensor_msgs/msg/LaserEcho[] ranges
sensor_msgs/msg/LaserEcho[] intensities
)RB"},
    {R"RB(sensor_msgs/msg/NavSatFix)RB", R"RB(uint8 COVARIANCE_TYPE_UNKNOWN=0
uint8 COVARIANCE_TYPE_APPROXIMATED=1
uint8 COVARIANCE_TYPE_DIAGONAL_KNOWN=2
uint8 COVARIANCE_TYPE_KNOWN=3
std_msgs/msg/Header header
sensor_msgs/msg/NavSatStatus status
float64 latitude
float64 longitude
float64 altitude
float64[9] position_covariance
uint8 position_covariance_type
)RB"},
    {R"RB(sensor_msgs/msg/NavSatStatus)RB", R"RB(int8 STATUS_UNKNOWN=-2
int8 STATUS_NO_FIX=-1
int8 STATUS_FIX=0
int8 STATUS_SBAS_FIX=1
int8 STATUS_GBAS_FIX=2
uint16 SERVICE_UNKNOWN=0
uint16 SERVICE_GPS=1
uint16 SERVICE_GLONASS=2
uint16 SERVICE_COMPASS=4
uint16 SERVICE_GALILEO=8
int8 status
uint16 service
)RB"},
    {R"RB(sensor_msgs/msg/PointCloud)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Point32[] points
sensor_msgs/msg/ChannelFloat32[] channels
)RB"},
    {R"RB(sensor_msgs/msg/PointCloud2)RB", R"RB(std_msgs/msg/Header header
uint32 height
uint32 width
sensor_msgs/msg/PointField[] fields
bool is_bigendian
uint32 point_step
uint32 row_step
uint8[] data
bool is_dense
)RB"},
    {R"RB(sensor_msgs/msg/PointField)RB", R"RB(uint8 INT8=1
uint8 UINT8=2
uint8 INT16=3
uint8 UINT16=4
uint8 INT32=5
uint8 UINT32=6
uint8 FLOAT32=7
uint8 FLOAT64=8
string name
uint32 offset
uint8 datatype
uint32 count
)RB"},
    {R"RB(sensor_msgs/msg/Range)RB", R"RB(uint8 ULTRASOUND=0
uint8 INFRARED=1
std_msgs/msg/Header header
uint8 radiation_type
float32 field_of_view
float32 min_range
float32 max_range
float32 range
float32 variance
)RB"},
    {R"RB(sensor_msgs/msg/RegionOfInterest)RB", R"RB(uint32 x_offset
uint32 y_offset
uint32 height
uint32 width
bool do_rectify
)RB"},
    {R"RB(sensor_msgs/msg/RelativeHumidity)RB", R"RB(std_msgs/msg/Header header
float64 relative_humidity
float64 variance
)RB"},
    {R"RB(sensor_msgs/msg/Temperature)RB", R"RB(std_msgs/msg/Header header
float64 temperature
float64 variance
)RB"},
    {R"RB(sensor_msgs/msg/TimeReference)RB", R"RB(std_msgs/msg/Header header
builtin_interfaces/msg/Time time_ref
string source
)RB"},
    {R"RB(service_msgs/msg/ServiceEventInfo)RB", R"RB(uint8 REQUEST_SENT=0
uint8 REQUEST_RECEIVED=1
uint8 RESPONSE_SENT=2
uint8 RESPONSE_RECEIVED=3
uint8 event_type
builtin_interfaces/msg/Time stamp
char[16] client_gid
int64 sequence_number
)RB"},
    {R"RB(shape_msgs/msg/Mesh)RB", R"RB(shape_msgs/msg/MeshTriangle[] triangles
geometry_msgs/msg/Point[] vertices
)RB"},
    {R"RB(shape_msgs/msg/MeshTriangle)RB", R"RB(uint32[3] vertex_indices
)RB"},
    {R"RB(shape_msgs/msg/Plane)RB", R"RB(float64[4] coef
)RB"},
    {R"RB(shape_msgs/msg/SolidPrimitive)RB", R"RB(uint8 BOX=1
uint8 SPHERE=2
uint8 CYLINDER=3
uint8 CONE=4
uint8 PRISM=5
uint8 BOX_X=0
uint8 BOX_Y=1
uint8 BOX_Z=2
uint8 SPHERE_RADIUS=0
uint8 CYLINDER_HEIGHT=0
uint8 CYLINDER_RADIUS=1
uint8 CONE_HEIGHT=0
uint8 CONE_RADIUS=1
uint8 PRISM_HEIGHT=0
uint8 type
float64[<=3] dimensions
geometry_msgs/msg/Polygon polygon
)RB"},
    {R"RB(statistics_msgs/msg/MetricsMessage)RB", R"RB(string measurement_source_name
string metrics_source
string unit
builtin_interfaces/msg/Time window_start
builtin_interfaces/msg/Time window_stop
statistics_msgs/msg/StatisticDataPoint[] statistics
)RB"},
    {R"RB(statistics_msgs/msg/StatisticDataPoint)RB", R"RB(uint8 data_type
float64 data
)RB"},
    {R"RB(statistics_msgs/msg/StatisticDataType)RB", R"RB(uint8 STATISTICS_DATA_TYPE_UNINITIALIZED=0
uint8 STATISTICS_DATA_TYPE_AVERAGE=1
uint8 STATISTICS_DATA_TYPE_MINIMUM=2
uint8 STATISTICS_DATA_TYPE_MAXIMUM=3
uint8 STATISTICS_DATA_TYPE_STDDEV=4
uint8 STATISTICS_DATA_TYPE_SAMPLE_COUNT=5
uint8 structure_needs_at_least_one_member
)RB"},
    {R"RB(std_msgs/msg/Bool)RB", R"RB(bool data
)RB"},
    {R"RB(std_msgs/msg/Byte)RB", R"RB(byte data
)RB"},
    {R"RB(std_msgs/msg/ByteMultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
byte[] data
)RB"},
    {R"RB(std_msgs/msg/Char)RB", R"RB(char data
)RB"},
    {R"RB(std_msgs/msg/ColorRGBA)RB", R"RB(float32 r
float32 g
float32 b
float32 a
)RB"},
    {R"RB(std_msgs/msg/Empty)RB", R"RB(uint8 structure_needs_at_least_one_member
)RB"},
    {R"RB(std_msgs/msg/Float32)RB", R"RB(float32 data
)RB"},
    {R"RB(std_msgs/msg/Float32MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
float32[] data
)RB"},
    {R"RB(std_msgs/msg/Float64)RB", R"RB(float64 data
)RB"},
    {R"RB(std_msgs/msg/Float64MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
float64[] data
)RB"},
    {R"RB(std_msgs/msg/Header)RB", R"RB(builtin_interfaces/msg/Time stamp
string frame_id
)RB"},
    {R"RB(std_msgs/msg/Int16)RB", R"RB(int16 data
)RB"},
    {R"RB(std_msgs/msg/Int16MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
int16[] data
)RB"},
    {R"RB(std_msgs/msg/Int32)RB", R"RB(int32 data
)RB"},
    {R"RB(std_msgs/msg/Int32MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
int32[] data
)RB"},
    {R"RB(std_msgs/msg/Int64)RB", R"RB(int64 data
)RB"},
    {R"RB(std_msgs/msg/Int64MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
int64[] data
)RB"},
    {R"RB(std_msgs/msg/Int8)RB", R"RB(int8 data
)RB"},
    {R"RB(std_msgs/msg/Int8MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
int8[] data
)RB"},
    {R"RB(std_msgs/msg/MultiArrayDimension)RB", R"RB(string label
uint32 size
uint32 stride
)RB"},
    {R"RB(std_msgs/msg/MultiArrayLayout)RB", R"RB(std_msgs/msg/MultiArrayDimension[] dim
uint32 data_offset
)RB"},
    {R"RB(std_msgs/msg/String)RB", R"RB(string data
)RB"},
    {R"RB(std_msgs/msg/UInt16)RB", R"RB(uint16 data
)RB"},
    {R"RB(std_msgs/msg/UInt16MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
uint16[] data
)RB"},
    {R"RB(std_msgs/msg/UInt32)RB", R"RB(uint32 data
)RB"},
    {R"RB(std_msgs/msg/UInt32MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
uint32[] data
)RB"},
    {R"RB(std_msgs/msg/UInt64)RB", R"RB(uint64 data
)RB"},
    {R"RB(std_msgs/msg/UInt64MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
uint64[] data
)RB"},
    {R"RB(std_msgs/msg/UInt8)RB", R"RB(uint8 data
)RB"},
    {R"RB(std_msgs/msg/UInt8MultiArray)RB", R"RB(std_msgs/msg/MultiArrayLayout layout
uint8[] data
)RB"},
    {R"RB(stereo_msgs/msg/DisparityImage)RB", R"RB(std_msgs/msg/Header header
sensor_msgs/msg/Image image
float32 f
float32 t
sensor_msgs/msg/RegionOfInterest valid_window
float32 min_disparity
float32 max_disparity
float32 delta_d
)RB"},
    {R"RB(tf2_msgs/msg/TF2Error)RB", R"RB(uint8 NO_ERROR=0
uint8 LOOKUP_ERROR=1
uint8 CONNECTIVITY_ERROR=2
uint8 EXTRAPOLATION_ERROR=3
uint8 INVALID_ARGUMENT_ERROR=4
uint8 TIMEOUT_ERROR=5
uint8 TRANSFORM_ERROR=6
uint8 error
string error_string
)RB"},
    {R"RB(tf2_msgs/msg/TFMessage)RB", R"RB(geometry_msgs/msg/TransformStamped[] transforms
)RB"},
    {R"RB(trajectory_msgs/msg/JointTrajectory)RB", R"RB(std_msgs/msg/Header header
string[] joint_names
trajectory_msgs/msg/JointTrajectoryPoint[] points
)RB"},
    {R"RB(trajectory_msgs/msg/JointTrajectoryPoint)RB", R"RB(float64[] positions
float64[] velocities
float64[] accelerations
float64[] effort
builtin_interfaces/msg/Duration time_from_start
)RB"},
    {R"RB(trajectory_msgs/msg/MultiDOFJointTrajectory)RB", R"RB(std_msgs/msg/Header header
string[] joint_names
trajectory_msgs/msg/MultiDOFJointTrajectoryPoint[] points
)RB"},
    {R"RB(trajectory_msgs/msg/MultiDOFJointTrajectoryPoint)RB", R"RB(geometry_msgs/msg/Transform[] transforms
geometry_msgs/msg/Twist[] velocities
geometry_msgs/msg/Twist[] accelerations
builtin_interfaces/msg/Duration time_from_start
)RB"},
    {R"RB(type_description_interfaces/msg/Field)RB", R"RB(string name
type_description_interfaces/msg/FieldType type
string default_value
)RB"},
    {R"RB(type_description_interfaces/msg/FieldType)RB", R"RB(uint8 FIELD_TYPE_NOT_SET=0
uint8 FIELD_TYPE_NESTED_TYPE=1
uint8 FIELD_TYPE_INT8=2
uint8 FIELD_TYPE_UINT8=3
uint8 FIELD_TYPE_INT16=4
uint8 FIELD_TYPE_UINT16=5
uint8 FIELD_TYPE_INT32=6
uint8 FIELD_TYPE_UINT32=7
uint8 FIELD_TYPE_INT64=8
uint8 FIELD_TYPE_UINT64=9
uint8 FIELD_TYPE_FLOAT=10
uint8 FIELD_TYPE_DOUBLE=11
uint8 FIELD_TYPE_LONG_DOUBLE=12
uint8 FIELD_TYPE_CHAR=13
uint8 FIELD_TYPE_WCHAR=14
uint8 FIELD_TYPE_BOOLEAN=15
uint8 FIELD_TYPE_BYTE=16
uint8 FIELD_TYPE_STRING=17
uint8 FIELD_TYPE_WSTRING=18
uint8 FIELD_TYPE_FIXED_STRING=19
uint8 FIELD_TYPE_FIXED_WSTRING=20
uint8 FIELD_TYPE_BOUNDED_STRING=21
uint8 FIELD_TYPE_BOUNDED_WSTRING=22
uint8 FIELD_TYPE_NESTED_TYPE_ARRAY=49
uint8 FIELD_TYPE_INT8_ARRAY=50
uint8 FIELD_TYPE_UINT8_ARRAY=51
uint8 FIELD_TYPE_INT16_ARRAY=52
uint8 FIELD_TYPE_UINT16_ARRAY=53
uint8 FIELD_TYPE_INT32_ARRAY=54
uint8 FIELD_TYPE_UINT32_ARRAY=55
uint8 FIELD_TYPE_INT64_ARRAY=56
uint8 FIELD_TYPE_UINT64_ARRAY=57
uint8 FIELD_TYPE_FLOAT_ARRAY=58
uint8 FIELD_TYPE_DOUBLE_ARRAY=59
uint8 FIELD_TYPE_LONG_DOUBLE_ARRAY=60
uint8 FIELD_TYPE_CHAR_ARRAY=61
uint8 FIELD_TYPE_WCHAR_ARRAY=62
uint8 FIELD_TYPE_BOOLEAN_ARRAY=63
uint8 FIELD_TYPE_BYTE_ARRAY=64
uint8 FIELD_TYPE_STRING_ARRAY=65
uint8 FIELD_TYPE_WSTRING_ARRAY=66
uint8 FIELD_TYPE_FIXED_STRING_ARRAY=67
uint8 FIELD_TYPE_FIXED_WSTRING_ARRAY=68
uint8 FIELD_TYPE_BOUNDED_STRING_ARRAY=69
uint8 FIELD_TYPE_BOUNDED_WSTRING_ARRAY=70
uint8 FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE=97
uint8 FIELD_TYPE_INT8_BOUNDED_SEQUENCE=98
uint8 FIELD_TYPE_UINT8_BOUNDED_SEQUENCE=99
uint8 FIELD_TYPE_INT16_BOUNDED_SEQUENCE=100
uint8 FIELD_TYPE_UINT16_BOUNDED_SEQUENCE=101
uint8 FIELD_TYPE_INT32_BOUNDED_SEQUENCE=102
uint8 FIELD_TYPE_UINT32_BOUNDED_SEQUENCE=103
uint8 FIELD_TYPE_INT64_BOUNDED_SEQUENCE=104
uint8 FIELD_TYPE_UINT64_BOUNDED_SEQUENCE=105
uint8 FIELD_TYPE_FLOAT_BOUNDED_SEQUENCE=106
uint8 FIELD_TYPE_DOUBLE_BOUNDED_SEQUENCE=107
uint8 FIELD_TYPE_LONG_DOUBLE_BOUNDED_SEQUENCE=108
uint8 FIELD_TYPE_CHAR_BOUNDED_SEQUENCE=109
uint8 FIELD_TYPE_WCHAR_BOUNDED_SEQUENCE=110
uint8 FIELD_TYPE_BOOLEAN_BOUNDED_SEQUENCE=111
uint8 FIELD_TYPE_BYTE_BOUNDED_SEQUENCE=112
uint8 FIELD_TYPE_STRING_BOUNDED_SEQUENCE=113
uint8 FIELD_TYPE_WSTRING_BOUNDED_SEQUENCE=114
uint8 FIELD_TYPE_FIXED_STRING_BOUNDED_SEQUENCE=115
uint8 FIELD_TYPE_FIXED_WSTRING_BOUNDED_SEQUENCE=116
uint8 FIELD_TYPE_BOUNDED_STRING_BOUNDED_SEQUENCE=117
uint8 FIELD_TYPE_BOUNDED_WSTRING_BOUNDED_SEQUENCE=118
uint8 FIELD_TYPE_NESTED_TYPE_UNBOUNDED_SEQUENCE=145
uint8 FIELD_TYPE_INT8_UNBOUNDED_SEQUENCE=146
uint8 FIELD_TYPE_UINT8_UNBOUNDED_SEQUENCE=147
uint8 FIELD_TYPE_INT16_UNBOUNDED_SEQUENCE=148
uint8 FIELD_TYPE_UINT16_UNBOUNDED_SEQUENCE=149
uint8 FIELD_TYPE_INT32_UNBOUNDED_SEQUENCE=150
uint8 FIELD_TYPE_UINT32_UNBOUNDED_SEQUENCE=151
uint8 FIELD_TYPE_INT64_UNBOUNDED_SEQUENCE=152
uint8 FIELD_TYPE_UINT64_UNBOUNDED_SEQUENCE=153
uint8 FIELD_TYPE_FLOAT_UNBOUNDED_SEQUENCE=154
uint8 FIELD_TYPE_DOUBLE_UNBOUNDED_SEQUENCE=155
uint8 FIELD_TYPE_LONG_DOUBLE_UNBOUNDED_SEQUENCE=156
uint8 FIELD_TYPE_CHAR_UNBOUNDED_SEQUENCE=157
uint8 FIELD_TYPE_WCHAR_UNBOUNDED_SEQUENCE=158
uint8 FIELD_TYPE_BOOLEAN_UNBOUNDED_SEQUENCE=159
uint8 FIELD_TYPE_BYTE_UNBOUNDED_SEQUENCE=160
uint8 FIELD_TYPE_STRING_UNBOUNDED_SEQUENCE=161
uint8 FIELD_TYPE_WSTRING_UNBOUNDED_SEQUENCE=162
uint8 FIELD_TYPE_FIXED_STRING_UNBOUNDED_SEQUENCE=163
uint8 FIELD_TYPE_FIXED_WSTRING_UNBOUNDED_SEQUENCE=164
uint8 FIELD_TYPE_BOUNDED_STRING_UNBOUNDED_SEQUENCE=165
uint8 FIELD_TYPE_BOUNDED_WSTRING_UNBOUNDED_SEQUENCE=166
uint8 type_id
uint64 capacity
uint64 string_capacity
string<=255 nested_type_name
)RB"},
    {R"RB(type_description_interfaces/msg/IndividualTypeDescription)RB", R"RB(string<=255 type_name
type_description_interfaces/msg/Field[] fields
)RB"},
    {R"RB(type_description_interfaces/msg/KeyValue)RB", R"RB(string key
string value
)RB"},
    {R"RB(type_description_interfaces/msg/TypeDescription)RB", R"RB(type_description_interfaces/msg/IndividualTypeDescription type_description
type_description_interfaces/msg/IndividualTypeDescription[] referenced_type_descriptions
)RB"},
    {R"RB(type_description_interfaces/msg/TypeSource)RB", R"RB(string type_name
string encoding
string raw_file_contents
)RB"},
    {R"RB(unique_identifier_msgs/msg/UUID)RB", R"RB(uint8[16] uuid
)RB"},
    {R"RB(visualization_msgs/msg/ImageMarker)RB", R"RB(int32 CIRCLE=0
int32 LINE_STRIP=1
int32 LINE_LIST=2
int32 POLYGON=3
int32 POINTS=4
int32 ADD=0
int32 REMOVE=1
std_msgs/msg/Header header
string ns
int32 id
int32 type
int32 action
geometry_msgs/msg/Point position
float32 scale
std_msgs/msg/ColorRGBA outline_color
uint8 filled
std_msgs/msg/ColorRGBA fill_color
builtin_interfaces/msg/Duration lifetime
geometry_msgs/msg/Point[] points
std_msgs/msg/ColorRGBA[] outline_colors
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarker)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Pose pose
string name
string description
float32 scale
visualization_msgs/msg/MenuEntry[] menu_entries
visualization_msgs/msg/InteractiveMarkerControl[] controls
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerControl)RB", R"RB(uint8 INHERIT=0
uint8 FIXED=1
uint8 VIEW_FACING=2
uint8 NONE=0
uint8 MENU=1
uint8 BUTTON=2
uint8 MOVE_AXIS=3
uint8 MOVE_PLANE=4
uint8 ROTATE_AXIS=5
uint8 MOVE_ROTATE=6
uint8 MOVE_3D=7
uint8 ROTATE_3D=8
uint8 MOVE_ROTATE_3D=9
string name
geometry_msgs/msg/Quaternion orientation
uint8 orientation_mode
uint8 interaction_mode
bool always_visible
visualization_msgs/msg/Marker[] markers
bool independent_marker_orientation
string description
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerFeedback)RB", R"RB(uint8 KEEP_ALIVE=0
uint8 POSE_UPDATE=1
uint8 MENU_SELECT=2
uint8 BUTTON_CLICK=3
uint8 MOUSE_DOWN=4
uint8 MOUSE_UP=5
std_msgs/msg/Header header
string client_id
string marker_name
string control_name
uint8 event_type
geometry_msgs/msg/Pose pose
uint32 menu_entry_id
geometry_msgs/msg/Point mouse_point
bool mouse_point_valid
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerInit)RB", R"RB(string server_id
uint64 seq_num
visualization_msgs/msg/InteractiveMarker[] markers
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerPose)RB", R"RB(std_msgs/msg/Header header
geometry_msgs/msg/Pose pose
string name
)RB"},
    {R"RB(visualization_msgs/msg/InteractiveMarkerUpdate)RB", R"RB(uint8 KEEP_ALIVE=0
uint8 UPDATE=1
string server_id
uint64 seq_num
uint8 type
visualization_msgs/msg/InteractiveMarker[] markers
visualization_msgs/msg/InteractiveMarkerPose[] poses
string[] erases
)RB"},
    {R"RB(visualization_msgs/msg/Marker)RB", R"RB(int32 ARROW=0
int32 CUBE=1
int32 SPHERE=2
int32 CYLINDER=3
int32 LINE_STRIP=4
int32 LINE_LIST=5
int32 CUBE_LIST=6
int32 SPHERE_LIST=7
int32 POINTS=8
int32 TEXT_VIEW_FACING=9
int32 MESH_RESOURCE=10
int32 TRIANGLE_LIST=11
int32 ARROW_STRIP=12
int32 ADD=0
int32 MODIFY=0
int32 DELETE=2
int32 DELETEALL=3
std_msgs/msg/Header header
string ns
int32 id
int32 type
int32 action
geometry_msgs/msg/Pose pose
geometry_msgs/msg/Vector3 scale
std_msgs/msg/ColorRGBA color
builtin_interfaces/msg/Duration lifetime
bool frame_locked
geometry_msgs/msg/Point[] points
std_msgs/msg/ColorRGBA[] colors
string texture_resource
sensor_msgs/msg/CompressedImage texture
visualization_msgs/msg/UVCoordinate[] uv_coordinates
string text
string mesh_resource
visualization_msgs/msg/MeshFile mesh_file
bool mesh_use_embedded_materials
)RB"},
    {R"RB(visualization_msgs/msg/MarkerArray)RB", R"RB(visualization_msgs/msg/Marker[] markers
)RB"},
    {R"RB(visualization_msgs/msg/MenuEntry)RB", R"RB(uint8 FEEDBACK=0
uint8 ROSRUN=1
uint8 ROSLAUNCH=2
uint32 id
uint32 parent_id
string title
string command
uint8 command_type
)RB"},
    {R"RB(visualization_msgs/msg/MeshFile)RB", R"RB(string filename
uint8[] data
)RB"},
    {R"RB(visualization_msgs/msg/UVCoordinate)RB", R"RB(float32 u
float32 v
)RB"},
};

void register_generated_types(std::unordered_map<std::string, TypeDef>& types, TypestorePreset preset) {
  const GeneratedTypeDefinition* definitions = nullptr;
  std::size_t count = 0;
  auto set = [&](const auto& table) {
    definitions = table;
    count = sizeof(table) / sizeof(table[0]);
  };
  switch (preset) {
    case TypestorePreset::Empty:
      set(kEmptyTypes);
      break;
    case TypestorePreset::Latest:
      set(kLatestTypes);
      break;
    case TypestorePreset::Ros1Noetic:
      set(kRos1NoeticTypes);
      break;
    case TypestorePreset::Ros2Dashing:
      set(kRos2DashingTypes);
      break;
    case TypestorePreset::Ros2Eloquent:
      set(kRos2EloquentTypes);
      break;
    case TypestorePreset::Ros2Foxy:
      set(kRos2FoxyTypes);
      break;
    case TypestorePreset::Ros2Galactic:
      set(kRos2GalacticTypes);
      break;
    case TypestorePreset::Ros2Humble:
      set(kRos2HumbleTypes);
      break;
    case TypestorePreset::Ros2Iron:
      set(kRos2IronTypes);
      break;
    case TypestorePreset::Ros2Jazzy:
      set(kRos2JazzyTypes);
      break;
    case TypestorePreset::Ros2Kilted:
      set(kRos2KiltedTypes);
      break;
  }
  for (std::size_t idx = 0; idx < count; ++idx) {
    parse_msg_body(types, definitions[idx].msgtype, definitions[idx].msgdef);
  }
}
