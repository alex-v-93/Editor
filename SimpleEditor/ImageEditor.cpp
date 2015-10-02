#include "stdafx.h"
#include "ImageEditor.h"
#include <opencv2\core.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
CImageEditor::CImageEditor(CString nameFile)
{
	CStringA pathA(nameFile);
	try
	{
		String s(pathA);
		m_img = make_shared<Mat>(imread(s));
		for (uint i = 0; i < 8; i++)
		{
			ImageEditItem item;
			item.typeEdit = (ImageEditType)i;
			item.value = 0;
			item.active = false;
			m_edits.push_back(item);
		}
	}
	catch (CMemoryException* e)
	{
		throw;
	}
	catch (CFileException* e)
	{
		throw;
	}
	catch (CException* e)
	{
		throw;
	}
}


CImageEditor::~CImageEditor()
{
}

void CImageEditor::InverseState(ImageEditType type)
{
	for (std::vector<ImageEditItem>::iterator iter = m_edits.begin(); iter != m_edits.end(); iter++)
	{
		if (iter->typeEdit == type)
			iter->active = !iter->active;
	}
	UpdateEdit();
}

void CImageEditor::IncrementValues()
{
	for (std::vector<ImageEditItem>::iterator iter = m_edits.begin(); iter != m_edits.end(); iter++)
	{
		if (iter->active)
			iter->value++;
	}
	UpdateEdit();
}

void CImageEditor::DecrementValues()
{
	for (std::vector<ImageEditItem>::iterator iter = m_edits.begin(); iter != m_edits.end(); iter++)
	{
		if (iter->active)
			iter->value--;
	}
	UpdateEdit();
}

void CImageEditor::UpdateEdit()
{
	m_imgEdit = make_shared<Mat>(m_img->clone());
	for (std::vector<ImageEditItem>::iterator iter = m_edits.begin(); iter != m_edits.end(); iter++)
	{
		if (iter->active && iter->value != 0)
		{
			if (iter->typeEdit == ImageEditType::Expo)
				Expo(iter->value);
			else if (iter->typeEdit == ImageEditType::Contrast)
				Contrast(iter->value);
			else if (iter->typeEdit == ImageEditType::Sature)
				Sature(iter->value);
			else if (iter->typeEdit == ImageEditType::Clarity)
				Clarity(iter->value);
			else if (iter->typeEdit == ImageEditType::White)
				White(iter->value);
			else if (iter->typeEdit == ImageEditType::Shadow)
				Shadow(iter->value);
			else if (iter->typeEdit == ImageEditType::Hue)
				Hue(iter->value);
			else if (iter->typeEdit == ImageEditType::Temperature)
				Temperature(iter->value);
		}
	}
}

void CImageEditor::Expo(int step)
{
	try
	{
		std::vector<Mat> hsv;
		cv::cvtColor(*m_imgEdit, *m_imgEdit, cv::ColorConversionCodes::COLOR_RGB2HSV_FULL);
		Mat lut = GetGammaExpo(step);
		cv::split(*m_imgEdit, hsv);
		LUT(hsv[2], lut, hsv[2]);
		cv::merge(hsv, *m_imgEdit);
		cv::cvtColor(*m_imgEdit, *m_imgEdit, cv::ColorConversionCodes::COLOR_HSV2RGB_FULL);
	}
	catch (Exception ex)
	{
		AfxMessageBox(CString(CStringA(ex.msg.begin())));
		throw;
	}
	catch (CMemoryException* e)
	{
		throw;
	}
	catch (CFileException* e)
	{
		throw;
	}
	catch (CException* e)
	{
		throw;
	}
}



void CImageEditor::Contrast(int step)
{
	try
	{
		std::vector<Mat> rgb;
		cv::split(*m_imgEdit, rgb);
		Mat lut(1, 256, CV_8UC1);
		double contrastLevel = /*std::pow(*/double(100 + step) / 100/*, 2)*/;
		uchar* p = lut.data;
		double d;
		for (int i = 0; i < 256; i++)
		{
			d = ((double(i) / 255 - 0.5)*contrastLevel + 0.5) * 255;
			if (d > 255)
				d = 255;
			if (d < 0)
				d = 0;
			p[i] = d;
		}
		LUT(rgb[0], lut, rgb[0]);
		LUT(rgb[1], lut, rgb[1]);
		LUT(rgb[2], lut, rgb[2]);
		cv::merge(rgb, *m_imgEdit);
	}
	catch (Exception ex)
	{
		AfxMessageBox(CString(CStringA(ex.msg.begin())));
		throw;
	}
	catch (CMemoryException* e)
	{
		throw;
	}
	catch (CFileException* e)
	{
		throw;
	}
	catch (CException* e)
	{
		throw;
	}

}

void CImageEditor::Sature(int step)
{
	try
	{
		std::vector<Mat> hsv;
		cv::cvtColor(*m_imgEdit, *m_imgEdit, cv::ColorConversionCodes::COLOR_RGB2HSV_FULL);
		cv::split(*m_imgEdit, hsv);
		hsv[1] += step * 5;
		cv::merge(hsv, *m_imgEdit);
		cv::cvtColor(*m_imgEdit, *m_imgEdit, cv::ColorConversionCodes::COLOR_HSV2RGB_FULL);
	}
	catch (Exception ex)
	{
		AfxMessageBox(CString(CStringA(ex.msg.begin())));
		throw;
	}
	catch (CMemoryException* e)
	{
		throw;
	}
	catch (CFileException* e)
	{
		throw;
	}
	catch (CException* e)
	{
		throw;
	}
}

void CImageEditor::Clarity(int step)
{
	try
	{
		if (step < 0)
		{
			cv::blur(*m_imgEdit, *m_imgEdit, cv::Size(-step * 2 + 1, -step * 2 + 1));
		}
		else
		{
			Mat dst = m_imgEdit->clone();
			float matr[9] {
						-0.0375 - 0.05*step, -0.0375 - 0.05*step, -0.0375 - 0.05*step,
						-0.0375 - 0.05*step, 1.3 + 0.4*step, -0.0375 - 0.05*step,
						-0.0375 - 0.05*step, -0.0375 - 0.05*step, -0.0375 - 0.05*step
			};
			Mat kernel_matrix = Mat(3, 3, CV_32FC1, &matr);
			cv::filter2D(*m_imgEdit, dst, 32, kernel_matrix);
			m_imgEdit = make_shared<Mat>(dst);
		}
	}
	catch (Exception ex)
	{
		AfxMessageBox(CString(CStringA(ex.msg.begin())));
		throw;
	}
	catch (CMemoryException* e)
	{
		
	}
	catch (CFileException* e)
	{
	}
	catch (CException* e)
	{
	}
}

void CImageEditor::White(int step)
{
	try
	{
		std::vector<Mat> hsv;
		cv::cvtColor(*m_imgEdit, *m_imgEdit, cv::ColorConversionCodes::COLOR_RGB2HSV_FULL);
		cv::split(*m_imgEdit, hsv);

		Mat lut = GetGammaLightShadow(step, true);
		LUT(hsv[2], lut, hsv[2]);
		cv::merge(hsv, *m_imgEdit);
		cv::cvtColor(*m_imgEdit, *m_imgEdit, cv::ColorConversionCodes::COLOR_HSV2RGB_FULL);
	}
	catch (Exception ex)
	{
		AfxMessageBox(CString(CStringA(ex.msg.begin())));
		throw;
	}
	catch (CMemoryException* e)
	{
		throw;
	}
	catch (CFileException* e)
	{
		throw;
	}
	catch (CException* e)
	{
		throw;
	}

}

void CImageEditor::Shadow(int step)
{
	try
	{
		std::vector<Mat> hsv;
		cv::cvtColor(*m_imgEdit, *m_imgEdit, cv::ColorConversionCodes::COLOR_RGB2HSV_FULL);
		cv::split(*m_imgEdit, hsv);

		Mat lut = GetGammaLightShadow(step, false);
		LUT(hsv[2], lut, hsv[2]);
		cv::merge(hsv, *m_imgEdit);
		cv::cvtColor(*m_imgEdit, *m_imgEdit, cv::ColorConversionCodes::COLOR_HSV2RGB_FULL);
	}
	catch (Exception ex)
	{
		AfxMessageBox(CString(CStringA(ex.msg.begin())));
		throw;
	}
	catch (CMemoryException* e)
	{
		throw;
	}
	catch (CFileException* e)
	{
		throw;
	}
	catch (CException* e)
	{
		throw;
	}
}

void CImageEditor::Hue(int step)
{
	try
	{
		std::vector<Mat> rgb;
		Mat lut0 = GetGammaExpo(step), lut1 = GetGammaExpo(-step), lut2 = GetGammaExpo(step);
		cv::split(*m_imgEdit, rgb);
		LUT(rgb[0], lut0, rgb[0]);
		LUT(rgb[1], lut1, rgb[1]);
		LUT(rgb[2], lut2, rgb[2]);
		cv::merge(rgb, *m_imgEdit);
	}
	catch (Exception ex)
	{
		AfxMessageBox(CString(CStringA(ex.msg.begin())));
		throw;
	}
	catch (CMemoryException* e)
	{
		throw;
	}
	catch (CFileException* e)
	{
		throw;
	}
	catch (CException* e)
	{
		throw;
	}
}

void CImageEditor::Temperature(int step)
{
	try
	{
		std::vector<Mat> rgb;
		Mat lut0 = GetGammaExpo(-step*2), lut1 = GetGammaExpo(step), lut2 = GetGammaExpo(step);
		cv::split(*m_imgEdit, rgb);
		LUT(rgb[0], lut0, rgb[0]);
		LUT(rgb[1], lut1, rgb[1]);
		LUT(rgb[2], lut2, rgb[2]);
		cv::merge(rgb, *m_imgEdit);
	}
	catch (Exception ex)
	{
		AfxMessageBox(CString(CStringA(ex.msg.begin())));
		throw;
	}
	catch (CMemoryException* e)
	{
		throw;
	}
	catch (CFileException* e)
	{
		throw;
	}
	catch (CException* e)
	{
		throw;
	}
}

byte CImageEditor::AddDoubleToByte(byte bt, double d)
{
	byte result = bt;
	if (double(result) + d > 255)
		result = 255;
	else if (double(result) + d < 0)
		result = 0;
	else
	{
		result += d;
	}
	return result;
}

bool CImageEditor::GetState(ImageEditType type)
{
	bool result = false;
	for (std::vector<ImageEditItem>::iterator iter = m_edits.begin(); iter != m_edits.end(); iter++)
	{
		if (iter->typeEdit == type)
			result = iter->active;
	}
	return result;
}

Mat CImageEditor::GetGammaLightShadow(int step, bool reverse)
{
	Mat result(1, 256, CV_8UC1);
	for (int i = 0; i < 256; i++)
	{
		*(result.data + i) = AddDoubleToByte(i, std::pow(0.36811145*M_E, 
			-std::pow(abs((reverse ? 256 : 0) - i), 1.7))*0.2*step*abs((reverse ? 256 : 0) - i));
	}
	return result;
}

cv::Mat CImageEditor::GetGammaExpo(int step)
{
	Mat result(1, 256, CV_8UC1);

	uchar* p = result.data;
	for (int i = 0; i < 256; i++)
	{
		p[i] = AddDoubleToByte(i, std::sin(i*k)*step * 10);
	}

	return result;
}

void CImageEditor::Save(LPCTSTR lpszPathName) const
{
	CStringA pathA(lpszPathName);
	if (m_imgEdit)
		cv::imwrite(String(pathA), *m_imgEdit);
}



