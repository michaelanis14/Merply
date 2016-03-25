/**************************************************************************
** File: rangevalidator.h
** Created on: 14.04.2015
** Author: Michael Bishara
** Copyright (C) 2015 Merply - Michael Bishara e.U.
**************************************************************************/

#ifndef RANGEVALIDATOR_H
#define RANGEVALIDATOR_H

#include <QDoubleValidator>
#include <QDebug>
class rangeValidator : public QDoubleValidator
{
public:
	rangeValidator(double bottom, double top, int decimals, QObject * parent = 0) :
		QDoubleValidator(bottom, top, decimals, parent)
	{
	}

	QValidator::State validate(QString &s, int &i ) const
	  {
		if(i){
		}
		  if (s.isEmpty() || s == "-") {
			  return QValidator::Intermediate;
		  }

		  QLocale locale;

		  QChar decimalPoint = locale.decimalPoint();
		  int charsAfterPoint = s.length() - s.indexOf(decimalPoint) -1;

		  if (charsAfterPoint > decimals() && s.indexOf(decimalPoint) != -1) {
			  return QValidator::Invalid;
		  }

		  bool ok;
		  double d = locale.toDouble(s, &ok);
		  if (ok && d >= bottom() && d <= top()) {
			  return QValidator::Acceptable;
		  } else {
			  return QValidator::Invalid;
		  }
	  }
};
#endif // RANGEVALIDATOR_H
