package demo;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Rectangle;
import java.util.Random;

import demo.MainFrame;

/** 

* @author 作者 侯丽娟: 

* @version 创建时间：2019年8月25日 下午8:31:38 

* 类说明 

*/
public class Egg {
	int row,col;	//定义鸡蛋坐标
	//定义鸡蛋大小
	int w=MainFrame.BLOCK_SIZE; //宽
	int h=MainFrame.BLOCK_SIZE; //高
	private Color color=Color.GRAY;//定义鸡蛋颜色
	
	private static Random random=new Random();
	
		//实例化Egg对象
		public Egg(int row,int col)
		{
			this.row=row;
			this.col=col;
		}
		//实例化Egg对象
		public Egg()
		{
			this(random.nextInt(MainFrame.ROWS-11)+6,random.nextInt(MainFrame.CLOS-8)+3);//保证鸡蛋在里面出现
		}	
		
		//画鸡蛋
		public void drawEgg(Graphics graphics)//接收graphics对象
		{
			Color c=graphics.getColor();
			graphics.setColor(color);
			graphics.fillOval(MainFrame.BLOCK_SIZE*col, MainFrame.BLOCK_SIZE*row, w, h);
			/*
			 * fillOval
			 *  x - 要填充椭圆的左上角的 x 坐标。
				y - 要填充椭圆的左上角的 y 坐标。
				width - 要填充椭圆的宽度。
				height - 要填充椭圆的高度。
			 */
			graphics.setColor(c);
			if(color==Color.GRAY)
			{
				color=Color.RED;
			}else{
				color=Color.GRAY;
			}
		}		
	
		//获取当前鸡蛋的坐标空间
		public Rectangle getRectangle(){
			Rectangle rectangle=new Rectangle(MainFrame.BLOCK_SIZE*col, MainFrame.BLOCK_SIZE*row, w, h);
			/*
			 * Rectangle(int x, int y, int width, int height) 
	                      构造一个新的 Rectangle，其左上角被指定为 (x,y)，其宽度和高度由同名的参数指定。
			 */
			return rectangle;
		}
		//显示新的鸡蛋
		public void drawNewEgg()
		{
			this.row=random.nextInt(MainFrame.ROWS-11)+6;
			this.col=random.nextInt(MainFrame.CLOS-8)+3;
		}
}
