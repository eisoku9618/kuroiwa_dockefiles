#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ode/ode.h>
#include <drawstuff/drawstuff.h>

#ifdef dDOUBLE
#define dsDrawCapsule dsDrawCapsuleD
#endif
#define NUM 2                          // リンク数

dWorldID      world;                   // 動力学計算用のワールド
dSpaceID      space;                   // 衝突検出用のスペース
dGeomID       ground;                  // 地面のジオメトリID番号
dJointGroupID contactgroup;            // 接触点グループ
dJointID      joint[NUM];              // ジョイントのID番号
dsFunctions   fn;                      // ドロースタッフの描画関数

typedef struct {
  dBodyID body;                        // ボディのID番号
  dGeomID geom;                        // ジオメトリのID番号
} MyObject;                            // MyObject構造体

MyObject rlink[NUM];                   // リンク
const dReal initial_theta = M_PI / 180 * 15;
dReal THETA = initial_theta;             // 関節の目標角度[rad]

// ロボットアームの生成
void  makeArm() {
  dMass mass;                                   // 質量パラメータ
  dReal x[NUM]      = {0.00, 0.00};             // 重心 x
  dReal y[NUM]      = {0.00, -0.50 * sin(initial_theta)}; // 重心 y
  dReal z[NUM]      = {0.50, 1.00 + 0.50 * cos(initial_theta)}; // 重心 z
  dReal length[NUM] = {1.00, 1.00};             // 長さ
  dReal weight[NUM] = {2.00, 2.00};             // 質量
  dReal r[NUM]      = {0.10, 0.10};             // 半径
  dReal c_x[NUM]    = {0.00, 0.00};             // 関節中心点 x
  dReal c_y[NUM]    = {0.00, 0.00};             // 関節中心点 y
  dReal c_z[NUM]    = {0.00, 1.00};             // 関節中心点 z
  dReal axis_x[NUM] = {0, 1};                   // 関節回転軸 x
  dReal axis_y[NUM] = {0, 0};                   // 関節回転軸 y
  dReal axis_z[NUM] = {0, 0};                   // 関節回転軸 z

  // リンクの生成
  for (int i = 0; i < NUM; ++i) {
    rlink[i].body = dBodyCreate(world);
    dBodySetPosition(rlink[i].body, x[i], y[i], z[i]);
    if (i == 1) {
      dMatrix3 R;
      dRFromAxisAndAngle(R, 1, 0, 0, initial_theta);
      dBodySetRotation(rlink[i].body, R);
    }
    dMassSetZero(&mass);
    dMassSetCapsuleTotal(&mass, weight[i], 3, r[i], length[i]);
    dBodySetMass(rlink[i].body, &mass);
    rlink[i].geom = dCreateCapsule(space, r[i], length[i]);
    dGeomSetBody(rlink[i].geom, rlink[i].body);
  }

  // ジョイントの生成とリンクへの取り付け
  joint[0] = dJointCreateFixed(world, 0); // 固定ジョイント
  dJointAttach(joint[0], rlink[0].body, 0);
  dJointSetFixed(joint[0]);
  for (int i = 1; i < NUM; ++i) {
    joint[i] = dJointCreateHinge(world, 0); // ヒンジジョイント
    dJointAttach(joint[i], rlink[i].body, rlink[i-1].body);
    dJointSetHingeAnchor(joint[i], c_x[i], c_y[i], c_z[i]);
    // dJointSetHingeAxis(joint[i], axis_x[i], axis_y[i], axis_z[i]);
    dJointSetHingeAxisOffset(joint[i], axis_x[i], axis_y[i], axis_z[i], initial_theta);
  }
}

// ロボットアームの描画
void drawArm() {
  for (int i = 0; i < NUM; ++i) { // カプセルの描画
    if (i == 0) {
      dsSetColor(1.0, 0.0, 0.0);
    } else {
      dsSetColor(0.0, 1.0, 0.0);
    }
    dReal r;
    dReal length;
    dGeomCapsuleGetParams(rlink[i].geom, &r, &length);
    dsDrawCapsule(dBodyGetPosition(rlink[i].body),
                  dBodyGetRotation(rlink[i].body),
                  length,
                  r);
  }
}

// P制御
void Pcontrol() {
  dReal k = 10.0;               // 比例ゲイン
  dReal fMax = 100.0;           // 最大トルク

  for (int i = 1; i < NUM; ++i) {
    dReal tmp = dJointGetHingeAngle(joint[i]);       // 関節角の取得
    dReal z = THETA - tmp;                        // 残差
    dJointSetHingeParam(joint[i], dParamVel, k * z); // 角速度の設定
    dJointSetHingeParam(joint[i], dParamFMax, fMax); // トルクの設定
    std::cout << "current: " << tmp / M_PI * 180 << std::endl;
  }
}

// 視点と視線の設定
void start() {
  float xyz[3] = {    3.0f, 1.3f, 0.8f};          // 視点[m]
  float hpr[3] = { -160.0f, 4.5f, 0.0f};          // 視線[°]
  dsSetViewpoint(xyz, hpr);                       // 視点と視線の設定
}

// キー入力関数
void command(int cmd) {
  switch (cmd) {
  case 'j': THETA += M_PI / 180; break;
  case 'k': THETA -= M_PI / 180; break;
  }
}

// シミュレーションループ
void simLoop(int pause) {
  Pcontrol();                                  // P制御
  dWorldStep(world, 0.01);                     // 動力学計算
  drawArm();                                   // ロボットの描画
}

// ドロースタッフの設定
void setDrawStuff() {
  fn.version = DS_VERSION;                     // バージョン番号
  fn.start   = &start;                         // start関数
  fn.step    = &simLoop;                       // simLoop関数
  fn.command = &command;                       // command関数
  fn.path_to_textures = "/tmp/ode/drawstuff/textures";
}

int main(int argc, char **argv) {
  dInitODE();                                     // ODEの初期化
  setDrawStuff();
  world        = dWorldCreate();                  // ワールドの生成
  space        = dHashSpaceCreate(0);             // スペースの生成
  contactgroup = dJointGroupCreate(0);            // 接触グループの生成
  ground       = dCreatePlane(space, 0, 0, 1, 0); // 地面の生成
  dWorldSetGravity(world, 0, 0, -9.8);            // 重力の設定
  makeArm();                                      // アームの生成
  dsSimulationLoop(argc, argv, 640, 480, &fn);    // シミュレーションループ
  dSpaceDestroy(space);                           // スペースの破壊
  dWorldDestroy(world);                           // ワールドの破壊
  dCloseODE();                                    // ODEの終了
  return 0;
}
