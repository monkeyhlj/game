package demo;

import java.awt.Color;
import java.awt.Font;
import java.awt.Frame;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.image.BufferedImage;
import java.io.FileInputStream;
import java.net.URL;
import java.awt.Toolkit;
import java.awt.event.WindowListener;

import javax.imageio.ImageIO;

/** 

* @author 作者 侯丽娟: 

* @version 创建时间：2019年8月23日 下午11:11:04 

* 类说明 

*/
public class MainFrame extends Frame{ //继承Frame类
	private static final long serialVersionUID = 1L;
			
	public static final int BLOCK_SIZE = 10;//定义小格子的宽和高
	public static final int  ROWS = 50;//定义行50个小格子
	public static final int CLOS = 50;//定义列
	
	public static BufferedImage bufferedImage = null;
	private static String imgPath = "img/backgrounds.jpg";//定义图片路径./src/img/backgrounds.jpg
	//private static String imageIcon = "img/icon.png";//定义左上角图片路径
	
	Snake snake = new Snake(this);//创建一个snake实例
	private PaintThread paintThread = new PaintThread();//见下：重新绘制-线程
	
	Egg egg = new Egg();//创建一个Egg实例
	private boolean gameOver=false;//定义属性判断是否去调用gameover()方法
	
	private int score = 0;//定义得分
	public int getScore() {
		return score;
	}
	public void setScore(int score) {
		this.score = score;
	}
	
	static {
		try {//加载图片路径
			bufferedImage = ImageIO.read(new FileInputStream(imgPath));
		} catch (Exception e) {
			// TODO: handle exception
		}
	}
	
	/**
	 * 初始化窗口
	 */
	public void init()
	{
		this.setLocation(500,100);//设置窗口起始位置
		/*URL url = this.getClass().getResource(imageIcon);//设置图标
		Image image = Toolkit.getDefaultToolkit().getImage(url);
		this.setIconImage(image);*/
		
		//设置窗体大小
		this.setSize(CLOS * BLOCK_SIZE-6, ROWS * BLOCK_SIZE-2);
		
		this.addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent e) {
				 System.exit(0);//设置窗体关闭
			}
		});
		//设置窗体可见
		this.setVisible(true);
		
		//增加监听事件
		this.addKeyListener(new KeyMoniter());
		//启动线程重新绘制
		new Thread(paintThread).start();
	}
	
	/**
	 * 画背景图  画鸡蛋、蛇  分数  游戏结束
	 */
	public void paint(Graphics g) {
		g.drawImage(bufferedImage, 0, 0, null);//背景图片
		if(gameOver){
			g.setColor(Color.YELLOW);
			g.setFont(new Font("宋体",Font.BOLD,50));
			g.drawString("游戏结束",140,180);
			paintThread.gameover();
		}
		g.setColor(Color.YELLOW);
		g.setFont(new Font("宋体",Font.BOLD,20));
		g.drawString("分数:"+score,20,60);
		snake.eat(egg);
		snake.draw(g);//画蛇
		egg.drawEgg(g);//画鸡蛋
	}
	
	
	//监听按键
	private class KeyMoniter extends KeyAdapter{
		@Override
		public void keyPressed(KeyEvent e) {
		snake.keyPressed(e);
		}
	}
	//重新绘制
	private class PaintThread implements Runnable{
		private boolean running=true;
		public void run(){
			while(running)
			{
				repaint();//重新绘制
				try {
					Thread.sleep(300);//设置蛇身移动速度
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		}
		public void gameover(){
			running=false;
		}
	}
	
	
	//解决背景闪烁问题
	Image image1=null;
	@Override
	public void update(Graphics g) { 
		 if(image1==null){
			 image1=this.createImage(CLOS*BLOCK_SIZE,ROWS*BLOCK_SIZE);
		 }
		 Graphics gsGraphics=image1.getGraphics();
		 paint(gsGraphics);
		 g.drawImage(image1, 0, 0, null);
	}	
	
	//蛇停止移动
	public void stop(){
		gameOver=true;
	}
	
	public static void main(String[] args){
		new MainFrame().init();
	}
}


