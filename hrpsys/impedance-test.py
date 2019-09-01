#!/usr/bin/env python

from hrpsys.hrpsys_config import *
import OpenHRP
from math import radians
from time import sleep

def init():
    global hcf, hrpsys_version
    hcf = HrpsysConfigurator()
    hcf.getRTCList = hcf.getRTCListUnstable
    hcf.init ("SampleRobot(Robot)0", "/opt/ros/indigo/share/OpenHRP-3.1/sample/model/sample1.wrl")
    # set initial pose from sample/controller/SampleController/etc/Sample.pos
    initial_pose =  [radians(x) for x in [0.0, -20.0, 0.0, 47.0, -27.0, 0.0, # rleg
                                          30.0, 0.0, 0.0, -60.0,  0.0, -60, 0, # rarm
                                          0.0, -20.0, 0.0, 47.0, -27.0, 0.0, # lleg
                                          30.0, 0.0, 0.0, -100.0, -9.0, -6.5, -36.5, # larm
                                          0.0, 0.0, 0.0] # torso
                 ]
    hcf.seq_svc.setJointAngles(initial_pose, 2.0)
    hcf.seq_svc.waitInterpolation()

def demo():
    hcf.removeForceSensorOffsetRMFO()
    hcf.clearLog()
    hcf.seq_svc.setWrenches([0, 0, 0, 0, 0, 0,
                             0, 0, 0, 0, 0, 0,
                             0, 0, 0, 0, 0, 0,
                             0, 0, 5, 0, 0, 0], 1.0);
    [_, icp] = hcf.ic_svc.getImpedanceControllerParam("rarm")
    icp.M_p = 100
    icp.D_p = 200
    icp.K_p = 100
    hcf.ic_svc.setImpedanceControllerParam("rarm", icp)
    sleep(2)
    hcf.startImpedance("rarm")
    hcf.seq_svc.waitInterpolation();
    sleep(10)
    hcf.stopImpedance("rarm")
    hcf.saveLog("/tmp/test-samplerobot-log")

if __name__ == '__main__':
    init()
    demo()
