#include "window.h"

//*******************************************************************************
//********	  Erebos	*********************************************************
//***Written by Cristian Lepadatu. Credits to TheChernoProject on youtube.com/
//*******************************************************************************
//
//Erebos  core engine - window class functions, and rogue functions
//	**Logic:
//		- graphics namespace
//	**Window class functions
//		- Non-default constructor Window(name, width, height) - assigns name, width, height as per instance
//		- 

namespace Erebos {
	namespace graphics{
		
		//-------------Rogue functions instantiation
		
		//-------------end
	
		//----Window constructors
		Window::Window(const char* name, int width, int height)
			{
				m_Title = name;
				m_Width = width;
				m_Height = height;
			
				//possible redundance, destroyst OpenGL window, cursor, resources. Investigate removal
				if (!init())
					glfwTerminate(); 

				for (int i = 0; i < MAX_KEYS; i++)
				{
					m_Keys[i] = false;

				}

				for (int i = 0; i < MAX_BUTTONS; i++)
				{
					m_MouseButtons[i] = false;

				}

			}

		Window::~Window()
		{
			glfwTerminate();
		}
		//----end

		//---Window methods
		bool Window::init() //-- Initialise GLFW Library, GLFW window creation, make window current, 
							//resize callback, initialise GLEW
			{
				
				if (!glfwInit() )//- Initialise GLFW Library,
					{
					std::cout << "Failed to initialize GLFW!" << std::endl;
					return false;
					}
				//-GLFWwindow creation
				m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
			
				if (!m_Window)
					{	
					glfwTerminate();
					std::cout << "Failed to create GLFW Window." << std::endl;
					return false;
					}
				//-Make GLFWwindow current
				glfwMakeContextCurrent(m_Window);
				//-Trigger for window resize callback (auto-function), triggers windowResize()
				glfwSetWindowUserPointer(m_Window, this);
				glfwSetWindowSizeCallback(m_Window,windowResize);
				glfwSetKeyCallback(m_Window, key_callback);
				glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
				glfwSetCursorPosCallback(m_Window, cursor_position_callback);

				//-Initialise GLEW
				if (glewInit() != GLEW_OK)
					{
					std::cout << "Could not initialise GLEW!" << std::endl;
					return false;
					}

				//Test print OpenGL version
				std::cout << "OpenGL" << glGetString(GL_VERSION) << std::endl;
				return true;

			}

		//--Tests window close flag, acts as game loop for now
		bool Window::closed() const
		{
			return glfwWindowShouldClose(m_Window)==1;
		}


		bool Window::isKeyPressed(unsigned int keycode) const
		{
			if (keycode >= MAX_KEYS)
				return false;
			return m_Keys[keycode];
		}

		bool Window::isMouseButtonPressed(unsigned int button) const
		{
			if (button >= MAX_BUTTONS)
				return false;
			return m_MouseButtons[button];
		}

		void Window::getMousePosition(double &x, double & y) const
		{
			x = m_Mx;
			y = m_My;
		}
		//--part of refresh screen
		void Window::clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		//draw updates
		void Window::update() 
		{

			GLenum error = glGetError();
			if (error != GL_NO_ERROR)
				std::cout << "OpenGL Error:" << error << std::endl;

			glfwPollEvents();//-process events in the event queue - eg input
//glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
			
			glfwSwapBuffers(m_Window);//Swap front and back buffers for rendering			
		}

		//--Resize window function
		void windowResize(GLFWwindow* window, int width, int height)
		{

			Window* win = (Window*)glfwGetWindowUserPointer(window);
			glViewport(0, 0, width, height);//sets viewport dimensions
			win->m_Width = width;
			win->m_Height = height;

		}

		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_Keys[key] = action != GLFW_RELEASE;

		}

		void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)

		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_MouseButtons[button] = action != GLFW_RELEASE;
		}
		void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_Mx = xpos;
			win->m_My = ypos;

		}
	}
}
