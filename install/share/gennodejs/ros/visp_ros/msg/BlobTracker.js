// Auto-generated. Do not edit!

// (in-package visp_ros.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let ImagePoint = require('./ImagePoint.js');
let ProjectedPoint = require('./ProjectedPoint.js');
let sensor_msgs = _finder('sensor_msgs');
let geometry_msgs = _finder('geometry_msgs');

//-----------------------------------------------------------

class BlobTracker {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.pose_stamped = null;
      this.image = null;
      this.blob_cogs = null;
      this.blob_proj = null;
    }
    else {
      if (initObj.hasOwnProperty('pose_stamped')) {
        this.pose_stamped = initObj.pose_stamped
      }
      else {
        this.pose_stamped = new geometry_msgs.msg.PoseStamped();
      }
      if (initObj.hasOwnProperty('image')) {
        this.image = initObj.image
      }
      else {
        this.image = new sensor_msgs.msg.Image();
      }
      if (initObj.hasOwnProperty('blob_cogs')) {
        this.blob_cogs = initObj.blob_cogs
      }
      else {
        this.blob_cogs = [];
      }
      if (initObj.hasOwnProperty('blob_proj')) {
        this.blob_proj = initObj.blob_proj
      }
      else {
        this.blob_proj = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type BlobTracker
    // Serialize message field [pose_stamped]
    bufferOffset = geometry_msgs.msg.PoseStamped.serialize(obj.pose_stamped, buffer, bufferOffset);
    // Serialize message field [image]
    bufferOffset = sensor_msgs.msg.Image.serialize(obj.image, buffer, bufferOffset);
    // Serialize message field [blob_cogs]
    // Serialize the length for message field [blob_cogs]
    bufferOffset = _serializer.uint32(obj.blob_cogs.length, buffer, bufferOffset);
    obj.blob_cogs.forEach((val) => {
      bufferOffset = ImagePoint.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [blob_proj]
    // Serialize the length for message field [blob_proj]
    bufferOffset = _serializer.uint32(obj.blob_proj.length, buffer, bufferOffset);
    obj.blob_proj.forEach((val) => {
      bufferOffset = ProjectedPoint.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type BlobTracker
    let len;
    let data = new BlobTracker(null);
    // Deserialize message field [pose_stamped]
    data.pose_stamped = geometry_msgs.msg.PoseStamped.deserialize(buffer, bufferOffset);
    // Deserialize message field [image]
    data.image = sensor_msgs.msg.Image.deserialize(buffer, bufferOffset);
    // Deserialize message field [blob_cogs]
    // Deserialize array length for message field [blob_cogs]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.blob_cogs = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.blob_cogs[i] = ImagePoint.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [blob_proj]
    // Deserialize array length for message field [blob_proj]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.blob_proj = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.blob_proj[i] = ProjectedPoint.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += geometry_msgs.msg.PoseStamped.getMessageSize(object.pose_stamped);
    length += sensor_msgs.msg.Image.getMessageSize(object.image);
    length += 16 * object.blob_cogs.length;
    length += 16 * object.blob_proj.length;
    return length + 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'visp_ros/BlobTracker';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '0dc82e760baf9b1ef9beb061604f3e2a';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    geometry_msgs/PoseStamped pose_stamped
    sensor_msgs/Image image
    ImagePoint[] blob_cogs
    ProjectedPoint[] blob_proj
    
    
    ================================================================================
    MSG: geometry_msgs/PoseStamped
    # A Pose with reference coordinate frame and timestamp
    Header header
    Pose pose
    
    ================================================================================
    MSG: std_msgs/Header
    # Standard metadata for higher-level stamped data types.
    # This is generally used to communicate timestamped data 
    # in a particular coordinate frame.
    # 
    # sequence ID: consecutively increasing ID 
    uint32 seq
    #Two-integer timestamp that is expressed as:
    # * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
    # * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
    # time-handling sugar is provided by the client library
    time stamp
    #Frame this data is associated with
    string frame_id
    
    ================================================================================
    MSG: geometry_msgs/Pose
    # A representation of pose in free space, composed of position and orientation. 
    Point position
    Quaternion orientation
    
    ================================================================================
    MSG: geometry_msgs/Point
    # This contains the position of a point in free space
    float64 x
    float64 y
    float64 z
    
    ================================================================================
    MSG: geometry_msgs/Quaternion
    # This represents an orientation in free space in quaternion form.
    
    float64 x
    float64 y
    float64 z
    float64 w
    
    ================================================================================
    MSG: sensor_msgs/Image
    # This message contains an uncompressed image
    # (0, 0) is at top-left corner of image
    #
    
    Header header        # Header timestamp should be acquisition time of image
                         # Header frame_id should be optical frame of camera
                         # origin of frame should be optical center of camera
                         # +x should point to the right in the image
                         # +y should point down in the image
                         # +z should point into to plane of the image
                         # If the frame_id here and the frame_id of the CameraInfo
                         # message associated with the image conflict
                         # the behavior is undefined
    
    uint32 height         # image height, that is, number of rows
    uint32 width          # image width, that is, number of columns
    
    # The legal values for encoding are in file src/image_encodings.cpp
    # If you want to standardize a new string format, join
    # ros-users@lists.sourceforge.net and send an email proposing a new encoding.
    
    string encoding       # Encoding of pixels -- channel meaning, ordering, size
                          # taken from the list of strings in include/sensor_msgs/image_encodings.h
    
    uint8 is_bigendian    # is this data bigendian?
    uint32 step           # Full row length in bytes
    uint8[] data          # actual matrix data, size is (step * rows)
    
    ================================================================================
    MSG: visp_ros/ImagePoint
    # Message corresponding to vpImagePoint class
    float64 i      # i (respectively v) position in the image
    float64 j      # j (respectively u) position in the image
    
    
    ================================================================================
    MSG: visp_ros/ProjectedPoint
    # Message corresponding to coordinates of the point after perspective projection
    float64 x      # Coordinate of the point in the image plane in meter along X axis
    float64 y      # Coordinate of the point in the image plane in meter along Y axis
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new BlobTracker(null);
    if (msg.pose_stamped !== undefined) {
      resolved.pose_stamped = geometry_msgs.msg.PoseStamped.Resolve(msg.pose_stamped)
    }
    else {
      resolved.pose_stamped = new geometry_msgs.msg.PoseStamped()
    }

    if (msg.image !== undefined) {
      resolved.image = sensor_msgs.msg.Image.Resolve(msg.image)
    }
    else {
      resolved.image = new sensor_msgs.msg.Image()
    }

    if (msg.blob_cogs !== undefined) {
      resolved.blob_cogs = new Array(msg.blob_cogs.length);
      for (let i = 0; i < resolved.blob_cogs.length; ++i) {
        resolved.blob_cogs[i] = ImagePoint.Resolve(msg.blob_cogs[i]);
      }
    }
    else {
      resolved.blob_cogs = []
    }

    if (msg.blob_proj !== undefined) {
      resolved.blob_proj = new Array(msg.blob_proj.length);
      for (let i = 0; i < resolved.blob_proj.length; ++i) {
        resolved.blob_proj[i] = ProjectedPoint.Resolve(msg.blob_proj[i]);
      }
    }
    else {
      resolved.blob_proj = []
    }

    return resolved;
    }
};

module.exports = BlobTracker;
