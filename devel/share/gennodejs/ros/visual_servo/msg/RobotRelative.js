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

class RobotRelative {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.actualTCPPose = null;
      this.targetTCPPose = null;
      this.actualTCPSpeed = null;
      this.targetTCPSpeed = null;
      this.actualTCPForce = null;
      this.actualToolAccel = null;
      this.actualJointPosition = null;
      this.end2base = null;
      this.digitalInputBits = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('actualTCPPose')) {
        this.actualTCPPose = initObj.actualTCPPose
      }
      else {
        this.actualTCPPose = [];
      }
      if (initObj.hasOwnProperty('targetTCPPose')) {
        this.targetTCPPose = initObj.targetTCPPose
      }
      else {
        this.targetTCPPose = [];
      }
      if (initObj.hasOwnProperty('actualTCPSpeed')) {
        this.actualTCPSpeed = initObj.actualTCPSpeed
      }
      else {
        this.actualTCPSpeed = [];
      }
      if (initObj.hasOwnProperty('targetTCPSpeed')) {
        this.targetTCPSpeed = initObj.targetTCPSpeed
      }
      else {
        this.targetTCPSpeed = [];
      }
      if (initObj.hasOwnProperty('actualTCPForce')) {
        this.actualTCPForce = initObj.actualTCPForce
      }
      else {
        this.actualTCPForce = [];
      }
      if (initObj.hasOwnProperty('actualToolAccel')) {
        this.actualToolAccel = initObj.actualToolAccel
      }
      else {
        this.actualToolAccel = [];
      }
      if (initObj.hasOwnProperty('actualJointPosition')) {
        this.actualJointPosition = initObj.actualJointPosition
      }
      else {
        this.actualJointPosition = [];
      }
      if (initObj.hasOwnProperty('end2base')) {
        this.end2base = initObj.end2base
      }
      else {
        this.end2base = [];
      }
      if (initObj.hasOwnProperty('digitalInputBits')) {
        this.digitalInputBits = initObj.digitalInputBits
      }
      else {
        this.digitalInputBits = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type RobotRelative
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [actualTCPPose]
    bufferOffset = _arraySerializer.float64(obj.actualTCPPose, buffer, bufferOffset, null);
    // Serialize message field [targetTCPPose]
    bufferOffset = _arraySerializer.float64(obj.targetTCPPose, buffer, bufferOffset, null);
    // Serialize message field [actualTCPSpeed]
    bufferOffset = _arraySerializer.float64(obj.actualTCPSpeed, buffer, bufferOffset, null);
    // Serialize message field [targetTCPSpeed]
    bufferOffset = _arraySerializer.float64(obj.targetTCPSpeed, buffer, bufferOffset, null);
    // Serialize message field [actualTCPForce]
    bufferOffset = _arraySerializer.float64(obj.actualTCPForce, buffer, bufferOffset, null);
    // Serialize message field [actualToolAccel]
    bufferOffset = _arraySerializer.float64(obj.actualToolAccel, buffer, bufferOffset, null);
    // Serialize message field [actualJointPosition]
    bufferOffset = _arraySerializer.float64(obj.actualJointPosition, buffer, bufferOffset, null);
    // Serialize message field [end2base]
    bufferOffset = _arraySerializer.float64(obj.end2base, buffer, bufferOffset, null);
    // Serialize message field [digitalInputBits]
    bufferOffset = _serializer.int64(obj.digitalInputBits, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type RobotRelative
    let len;
    let data = new RobotRelative(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [actualTCPPose]
    data.actualTCPPose = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [targetTCPPose]
    data.targetTCPPose = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [actualTCPSpeed]
    data.actualTCPSpeed = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [targetTCPSpeed]
    data.targetTCPSpeed = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [actualTCPForce]
    data.actualTCPForce = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [actualToolAccel]
    data.actualToolAccel = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [actualJointPosition]
    data.actualJointPosition = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [end2base]
    data.end2base = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [digitalInputBits]
    data.digitalInputBits = _deserializer.int64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    length += 8 * object.actualTCPPose.length;
    length += 8 * object.targetTCPPose.length;
    length += 8 * object.actualTCPSpeed.length;
    length += 8 * object.targetTCPSpeed.length;
    length += 8 * object.actualTCPForce.length;
    length += 8 * object.actualToolAccel.length;
    length += 8 * object.actualJointPosition.length;
    length += 8 * object.end2base.length;
    return length + 40;
  }

  static datatype() {
    // Returns string type for a message object
    return 'visual_servo/RobotRelative';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '43b4d3212a47865eb33311ebedb438ce';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    float64[] actualTCPPose
    float64[] targetTCPPose
    float64[] actualTCPSpeed
    float64[] targetTCPSpeed
    float64[] actualTCPForce
    float64[] actualToolAccel
    float64[] actualJointPosition
    float64[] end2base
    int64 digitalInputBits
    
    
    
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
    const resolved = new RobotRelative(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.actualTCPPose !== undefined) {
      resolved.actualTCPPose = msg.actualTCPPose;
    }
    else {
      resolved.actualTCPPose = []
    }

    if (msg.targetTCPPose !== undefined) {
      resolved.targetTCPPose = msg.targetTCPPose;
    }
    else {
      resolved.targetTCPPose = []
    }

    if (msg.actualTCPSpeed !== undefined) {
      resolved.actualTCPSpeed = msg.actualTCPSpeed;
    }
    else {
      resolved.actualTCPSpeed = []
    }

    if (msg.targetTCPSpeed !== undefined) {
      resolved.targetTCPSpeed = msg.targetTCPSpeed;
    }
    else {
      resolved.targetTCPSpeed = []
    }

    if (msg.actualTCPForce !== undefined) {
      resolved.actualTCPForce = msg.actualTCPForce;
    }
    else {
      resolved.actualTCPForce = []
    }

    if (msg.actualToolAccel !== undefined) {
      resolved.actualToolAccel = msg.actualToolAccel;
    }
    else {
      resolved.actualToolAccel = []
    }

    if (msg.actualJointPosition !== undefined) {
      resolved.actualJointPosition = msg.actualJointPosition;
    }
    else {
      resolved.actualJointPosition = []
    }

    if (msg.end2base !== undefined) {
      resolved.end2base = msg.end2base;
    }
    else {
      resolved.end2base = []
    }

    if (msg.digitalInputBits !== undefined) {
      resolved.digitalInputBits = msg.digitalInputBits;
    }
    else {
      resolved.digitalInputBits = 0
    }

    return resolved;
    }
};

module.exports = RobotRelative;
