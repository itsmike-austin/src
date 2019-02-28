package com.example.killthemall;

import android.annotation.SuppressLint;
import android.graphics.Canvas;

public class GameLoopThread extends Thread
{
	static final long FPS = 10;
	private GameView view;
	private boolean running = false;
	
	public GameLoopThread(GameView view)
	{
		this.view = view;
	}
	
	public void setRunning(boolean run)
	{
		running = run;
	}
	
	@SuppressLint("WrongCall")
	@Override
	public void run()
	{
		long ticksPS = 1000 / FPS;
		long startTime;
		long sleepTime;
		
		while ( running )
		{
			Canvas c = null;
			
			// Get the current time for 10ms frame per second calcs
			
			startTime = System.currentTimeMillis();
			
			// Draw the canvas
			
			try {
				c = view.getHolder().lockCanvas();
				synchronized(view.getHolder())
				{
					view.onDraw(c);
				}
			}finally {
				if ( c != null )
				{
					view.getHolder().unlockCanvasAndPost(c);
				}
			}
			
			// Delay the rest of the 10ms before returning.
			
			sleepTime = ticksPS - (System.currentTimeMillis() - startTime);
			
			try
			{
				if ( sleepTime > 0 )
				{
					sleep(sleepTime);
				}
				else
				{
					sleep(10);
				}
			}catch (Exception e ) {}
		}
	}
}