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

class pbvs_circles {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.circle1 = null;
      this.circle2 = null;
      this.circle3 = null;
      this.circle4 = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('circle1')) {
        this.circle1 = initObj.circle1
      }
      else {
        this.circle1 = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('circle2')) {
        this.circle2 = initObj.circle2
      }
      else {
        this.circle2 = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('circle3')) {
        this.circle3 = initObj.circle3
      }
      else {
        this.circle3 = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('circle4')) {
        this.circle4 = initObj.circle4
      }
      else {
        this.circle4 = new Array(3).fill(0);
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type pbvs_circles
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Check that the constant length array field [circle1] has the right length
    if (obj.circle1.length !== 3) {
      throw new Error('Unable to serialize array field circle1 - length must be 3')
    }
    // Serialize message field [circle1]
    bufferOffset = _arraySerializer.float32(obj.circle1, buffer, bufferOffset, 3);
    // Check that the constant length array field [circle2] has the right length
    if (obj.circle2.length !== 3) {
      throw new Error('Unable to serialize array field circle2 - length must be 3')
    }
    // Serialize message field [circle2]
    bufferOffset = _arraySerializer.float32(obj.circle2, buffer, bufferOffset, 3);
    // Check that the constant length array field [circle3] has the right length
    if (obj.circle3.length !== 3) {
      throw new Error('Unable to serialize array field circle3 - length must be 3')
    }
    // Serialize message field [circle3]
    bufferOffset = _arraySerializer.float32(obj.circle3, buffer, bufferOffset, 3);
    // Check that the constant length array field [circle4] has the right length
    if (obj.circle4.length !== 3) {
      throw new Error('Unable to serialize array field circle4 - length must be 3')
    }
    // Serialize message field [circle4]
    bufferOffset = _arraySerializer.float32(obj.circle4, buffer, bufferOffset, 3);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type pbvs_circles
    let len;
    let data = new pbvs_circles(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [circle1]
    data.circle1 = _arrayDeserializer.float32(buffer, bufferOffset, 3)
    // Deserialize message field [circle2]
    data.circle2 = _arrayDeserializer.float32(buffer, bufferOffset, 3)
    // Deserialize message field [circle3]
    data.circle3 = _arrayDeserializer.float32(buffer, bufferOffset, 3)
    // Deserialize message field [circle4]
    data.circle4 = _arrayDeserializer.float32(buffer, bufferOffset, 3)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 48;
  }

  static datatype() {
    // Returns string type for a message object
    return 'visual_servo/pbvs_circles';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'f98297f55b162ac720ff220dc219f92d';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    std_msgs/Header header
    float32[3] circle1
    float32[3] circle2
    float32[3] circle3
    float32[3] circle4
    
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
    const resolved = new pbvs_circles(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.circle1 !== undefined) {
      resolved.circle1 = msg.circle1;
    }
    else {
      resolved.circle1 = new Array(3).fill(0)
    }

    if (msg.circle2 !== undefined) {
      resolved.circle2 = msg.circle2;
    }
    else {
      resolved.circle2 = new Array(3).fill(0)
    }

    if (msg.circle3 !== undefined) {
      resolved.circle3 = msg.circle3;
    }
    else {
      resolved.circle3 = new Array(3).fill(0)
    }

    if (msg.circle4 !== undefined) {
      resolved.circle4 = msg.circle4;
    }
    else {
      resolved.circle4 = new Array(3).fill(0)
    }

    return resolved;
    }
};

module.exports = pbvs_circles;
