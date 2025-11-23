#pragma once

#include <QOpenGLWidget>

namespace Lumin
{
	class LEngine;
	struct LViewportConfig
	{
		int width;
		int height;
		LEngine* engine;
	};

	class LViewport : public QOpenGLWidget
	{
		Q_OBJECT

	public:
		LViewport(const LViewportConfig& config, QWidget* parent = nullptr);
		~LViewport();

		bool ViewportShouldClose() const;
	protected:
		void initializeGL() override;
		void resizeGL(int w, int h) override;
		void paintGL() override;
		void keyPressEvent(QKeyEvent* event) override;
		void keyReleaseEvent(QKeyEvent* event) override;
		void closeEvent(QCloseEvent* event) override;
	private:
		bool m_canShow = true;
		LEngine* m_engine;
	};


}
