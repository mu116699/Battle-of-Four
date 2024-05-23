# Battle-of-Four（四子决）

四子决开源模型文档

1. 棋盘构成如下：
    棋盘为四横四纵，红蓝双方各有四子。
    棋格标号采用横向英文，纵向数字。
    所有棋格、棋子享有同等地位。
    中间洋红部分为中原地带。
    四路纵向出击战线，左右战线为左右翼路，中间两路为出击战线。
    中间横向战线为前沿战线。

<div align="center">
  <img src="https://github.com/mu116699/Battle-of-Four/blob/master/IMG/Checkerboard.png" alt="Checkerboard">
</div>

3. 游戏玩法
    杀对面子时为主动动作，不是被动动作。
    规则就是两个子可以杀掉对面的一个子。
    都是两个子时是没有办法杀掉对方的。

<div align="center">
  <img src="https://github.com/mu116699/Battle-of-Four/blob/master/IMG/Rule.png" alt="Rule">
</div>

5. 获胜的条件
    对方只剩下一个子时。
    无子可走时即为获胜。

<div align="center">
  <img src="https://github.com/mu116699/Battle-of-Four/blob/master/IMG/Victory.png" alt="Victory">
</div>

7. 提供相关语音API，玩法简单，改变规则容易实现多种语音模型。
8. 提供相关智能算法API，可是快速集成智能算法，供初学者学习机器学习算法、神经网络等算法。

初步运用 java swing 和 awt 框架实现该游戏代码，希望有志之士共同完成，该代码后续部分完全开源。
