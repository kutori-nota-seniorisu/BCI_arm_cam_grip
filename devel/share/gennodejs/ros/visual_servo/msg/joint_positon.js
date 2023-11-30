// Auto-generated. Do not edit!

// (in-package visual_servo.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class joint_positon {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.shoulder_pan_joint = null;
      this.shoulder_lift_joint = null;
      this.elbow_joint = null;
      this.wrist_1_joint = null;
      this.wrist_2_joint = null;
      this.wrist_3_joint = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('shoulder_pan_joint')) {
        this.shoulder_pan_joint = initObj.shoulder_pan_joint
      }
      else {
        this.shoulder_pan_joint = 0.0;
      }
      if (initObj.hasOwnProperty('shoulder_lift_joint')) {
        this.shoulder_lift_joint = initObj.shoulder_lift_joint
      }
      else {
        this.shoulder_lift_joint = 0.0;
      }
      if (initObj.hasOwnProperty('elbow_joint')) {
        this.elbow_joint = initObj.elbow_joint
      }
      else {
        this.elbow_joint = 0.0;
      }
      if (initObj.hasOwnProperty('wrist_1_joint')) {
        this.wrist_1_joint = initObj.wrist_1_joint
      }
      else {
        this.wrist_1_joint = 0.0;
      }
      if (initObj.hasOwnProperty('wrist_2_joint')) {
        this.wrist_2_joint = initObj.wrist_2_joint
      }
      else {
        this.wrist_2_joint = 0.0;
      }
      if (initObj.hasOwnProperty('wrist_3_joint')) {
        this.wrist_3_joint = initObj.wrist_3_joint
      }
      else {
        this.wrist_3_joint = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type joint_positon
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [shoulder_pan_joint]
    bufferOffset = _serializer.float32(obj.shoulder_pan_joint, buffer, bufferOffset);
    // Serialize message field [shoulder_lift_joint]
    bufferOffset = _serializer.float32(obj.shoulder_lift_joint, buffer, bufferOffset);
    // Serialize message field [elbow_joint]
    bufferOffset = _serializer.float32(obj.elbow_joint, buffer, bufferOffset);
    // Serialize message field [wrist_1_joint]
    bufferOffset = _serializer.float32(obj.wrist_1_joint, buffer, bufferOffset);
    // Serialize message field [wrist_2_joint]
    bufferOffset = _serializer.float32(obj.wrist_2_joint, buffer, bufferOffset);
    // Serialize message field [wrist_3_joint]
    bufferOffset = _serializer.float32(obj.wrist_3_joint, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type joint_positon
    let len;
    let data = new joint_positon(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [shoulder_pan_joint]
    data.shoulder_pan_joint = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [shoulder_lift_joint]
    data.shoulder_lift_joint = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [elbow_joint]
    data.elbow_joint = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [wrist_1_joint]
    data.wrist_1_joint = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [wrist_2_joint]
    data.wrist_2_joint = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [wrist_3_joint]
    data.wrist_3_joint = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 24;
  }

  static datatype() {
    // Returns string type for a message object
    return 'visual_servo/joint_positon';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'a82fc01b03f66381c43297a78b5259f1';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    std_msgs/Header header
    float32 shoulder_pan_joint
    float32 shoulder_lift_joint
    float32 elbow_joint
    float32 wrist_1_joint
    float32 wrist_2_joint
    float32 wrist_3_joint
    
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new joint_positon(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.shoulder_pan_joint !== undefined) {
      resolved.shoulder_pan_joint = msg.shoulder_pan_joint;
    }
    else {
      resolved.shoulder_pan_joint = 0.0
    }

    if (msg.shoulder_lift_joint !== undefined) {
      resolved.shoulder_lift_joint = msg.shoulder_lift_joint;
    }
    else {
      resolved.shoulder_lift_joint = 0.0
    }

    if (msg.elbow_joint !== undefined) {
      resolved.elbow_joint = msg.elbow_joint;
    }
    else {
      resolved.elbow_joint = 0.0
    }

    if (msg.wrist_1_joint !== undefined) {
      resolved.wrist_1_joint = msg.wrist_1_joint;
    }
    else {
      resolved.wrist_1_joint = 0.0
    }

    if (msg.wrist_2_joint !== undefined) {
      resolved.wrist_2_joint = msg.wrist_2_joint;
    }
    else {
      resolved.wrist_2_joint = 0.0
    }

    if (msg.wrist_3_joint !== undefined) {
      resolved.wrist_3_joint = msg.wrist_3_joint;
    }
    else {
      resolved.wrist_3_joint = 0.0
    }

    return resolved;
    }
};

module.exports = joint_positon;
