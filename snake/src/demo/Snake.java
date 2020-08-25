package demo;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Rectangle;
import java.awt.event.KeyEvent;

import demo.Direction;
import demo.MainFrame;
import demo.Egg;

/** 

* @author 作者 侯丽娟: 

* @version 创建时间：2019年8月25日 下午8:07:02 

* 类说明 

*/
public class Snake {
	private Node head = null;//定义头
	private Node tail = null;//定义尾巴
	private int size=0;//定义蛇的大小，多少节
	
	//初始化一个蛇身节点
	private Node node=new Node(20,20,Direction.Up);
	private MainFrame mainFrame;
	
	private class Node{		//定义节点 该类是蛇身
		int w=MainFrame.BLOCK_SIZE; //宽度  
		int h=MainFrame.BLOCK_SIZE; //高度
		int row,col; //定义位置，第几行第几列
		Direction direction=Direction.Left; //方向
		Node next=null;
		Node prev=null;//双向链表
		
		Node(int row,int col,Direction direction){
			this.row=row;
			this.col=col;
			this.direction=direction;
		}
		
		void draw(Graphics g)
		{
			//Color color=g.getColor();
			g.setColor(Color.BLACK);//设置颜色
			g.fillRect(MainFrame.BLOCK_SIZE*col, MainFrame.BLOCK_SIZE*row, w, h);
			/*填写指定的矩形
			 *  x - 要填充矩形的 x 坐标。
				y - 要填充矩形的 y 坐标。
				width - 要填充矩形的宽度。
				height - 要填充矩形的高度。
			 */
		}
	}
	
	/**
	 * 实例化snake对象，并且初始化头尾节点相同
	 * @param mainFrame 接收主界面对象参数
	 */
	public Snake(MainFrame mainFrame)
	{
		head=node;
		tail=node;
		size=1;
		this.mainFrame=mainFrame;
	}
	
	public void addToHead()//添加到头
	{
		Node node=null;
		switch(head.direction)
		{
			case Up:
				node=new Node(head.row-1,head.col,head.direction);
				break;
			case Down:
				node=new Node(head.row+1,head.col,head.direction);
				break;
			case Left:
				node=new Node(head.row,head.col-1,head.direction);
				break;
			case Right:
				node=new Node(head.row,head.col+1,head.direction);
				break;
		}
		node.next=head;
		head.prev=node;
		head=node;
		size++;
	}
	
	/**
	 * 按键方法：判断是选择哪个方向键
	 * @param e 接收KeyEvent对象参数
	 */
	public void keyPressed(KeyEvent e)
	{
		int key=e.getKeyCode();//获取按下键盘对应的数字
		switch(key)
		{
			case KeyEvent.VK_LEFT:
				if(head.direction != Direction.Right){
					head.direction=Direction.Left;
				}
				break;
			case KeyEvent.VK_RIGHT:
				if(head.direction != Direction.Left){
					head.direction=Direction.Right;
				}
				break;
			case KeyEvent.VK_UP:
				if(head.direction != Direction.Down){
					head.direction=Direction.Up;
				}
				break;
			case KeyEvent.VK_DOWN:
				if(head.direction != Direction.Up){
					head.direction=Direction.Down;
				}
				break;
		}
	}
	
	
	/**
	 * 绘制蛇
	 * @param g 接收Graphics对象参数
	 */
	public void draw(Graphics g)
	{
		if(size <=0)
		{
			return ;
		}
		move();
		for(Node node=head;node!=null;node=node.next)
		{
			node.draw(g);
		}
	}
	
		//蛇身移动
		private void move()
		{
			addToHead();
			deleteFromTail();
			checkHead();
		}
		//删除最后一节
		private void deleteFromTail()
		{
			if(size==0)
			{
				return;
			}
			tail = tail.prev;
			tail.next=null;
		}
		//判断是不是撞墙 	判断蛇头是否与蛇尾相撞
			private void checkHead()
			{
				if(head.row<6 || head.col<3 || head.row>MainFrame.ROWS-5 || head.col>MainFrame.CLOS-5){
					mainFrame.stop();
				}
				for(Node node=head.next;node!=null;node=node.next){
					if(head.row==node.row && head.col==node.col){
						mainFrame.stop();
					}
				}
			}		
			
	
			//获取当前蛇头的坐标空间
			public Rectangle getRectangle(){
				Rectangle rectangle=new Rectangle(MainFrame.BLOCK_SIZE*head.col, MainFrame.BLOCK_SIZE*head.row, head.w, head.h);
				return rectangle;
			}
			//蛇吃鸡蛋
			public void eat(Egg egg){
				if(this.getRectangle().intersects(egg.getRectangle())){//判断是否相撞
					egg.drawNewEgg();
					this.addToHead();
					mainFrame.setScore(mainFrame.getScore()+5);
				}
			}
	
}
