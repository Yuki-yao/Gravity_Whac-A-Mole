// pages/mypage.js
import bleComm from '../utils/bleComm.js';
const zeroth = 0.05;
const speed = 30;
Page({

  /**
   * 页面的初始数据
   */
  data: {
    curX: 0,
    curY: 0
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    wx.showLoading({
      title: '靠近连接',
      mask: true
    });
    bleComm.connectDevice().then(res => {
      wx.showToast({
        title: '蓝牙连接成功',
        icon: 'success',
        duration: 300
      });
    });
    var that = this;
    wx.onAccelerometerChange(function(res){
      if(res.x != undefined && res.y != undefined) {
        that.setData({
          curX: res.x,
          curY: res.y
        });
        if(res.y > zeroth || res.y < -zeroth) {
          bleComm.writeValue(parseInt(res.y * speed) + '\n');
        }
      }
    });
  },

  /**
   * 生命周期函数--监听页面初次渲染完成
   */
  onReady: function () {
  
  },

  /**
   * 生命周期函数--监听页面显示
   */
  onShow: function () {
  
  },

  /**
   * 生命周期函数--监听页面隐藏
   */
  onHide: function () {
    bleComm.disConnect();
  },

  /**
   * 生命周期函数--监听页面卸载
   */
  onUnload: function () {
    bleComm.disConnect();
  },

  /**
   * 页面相关事件处理函数--监听用户下拉动作
   */
  onPullDownRefresh: function () {
  
  },

  /**
   * 页面上拉触底事件的处理函数
   */
  onReachBottom: function () {
  
  },

  /**
   * 用户点击右上角分享
   */
  onShareAppMessage: function () {
  
  }
})