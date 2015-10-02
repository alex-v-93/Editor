#pragma once
#include <memory>
#include <afxstr.h>
#include <opencv2\core\mat.hpp>

enum ImageEditType
{
	Expo = 0,
	Contrast = 1,
	Sature = 2,
	Clarity = 3,
	White = 4,
	Shadow = 5,
	Hue = 6,
	Temperature = 7
};

struct ImageEditItem
{
	ImageEditType typeEdit;
	int value;
	bool active;
};

class CImageEditor
{
	double k = 0.01255;
	std::shared_ptr<Mat> m_img;
	std::shared_ptr<Mat> m_imgEdit;
	std::vector<ImageEditItem> m_edits;
public:
	CImageEditor(CString nameFile);
	~CImageEditor();

	std::shared_ptr<Mat> GetImage() { return  m_imgEdit ? m_imgEdit : m_img; }
	void InverseState(ImageEditType type);
	bool GetState(ImageEditType type);
	void IncrementValues();
	void DecrementValues();
	void UpdateEdit();
	void Save(LPCTSTR lpszPathName) const;
private:
	void Expo(int step);
	void Contrast(int step);
	void Sature(int step);
	void Clarity(int step);
	void White(int step);
	void Shadow(int step);
	void Hue(int step);
	void Temperature(int step);

	byte AddDoubleToByte(byte bt, double d);
	Mat GetGammaLightShadow(int step, bool reverse);
	Mat GetGammaExpo(int step);
	
};

