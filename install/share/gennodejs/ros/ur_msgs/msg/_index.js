
"use strict";

let Digital = require('./Digital.js');
let MasterboardDataMsg = require('./MasterboardDataMsg.js');
let IOStates = require('./IOStates.js');
let ToolDataMsg = require('./ToolDataMsg.js');
let RobotModeDataMsg = require('./RobotModeDataMsg.js');
let RobotStateRTMsg = require('./RobotStateRTMsg.js');
let Analog = require('./Analog.js');

module.exports = {
  Digital: Digital,
  MasterboardDataMsg: MasterboardDataMsg,
  IOStates: IOStates,
  ToolDataMsg: ToolDataMsg,
  RobotModeDataMsg: RobotModeDataMsg,
  RobotStateRTMsg: RobotStateRTMsg,
  Analog: Analog,
};
