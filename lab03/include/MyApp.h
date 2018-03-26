#ifndef INCLUDED_MYAPP_H
#define INCLUDED_MYAPP_H
 
class MyApp : public wxApp
{
public:
	virtual bool OnInit();
};
 
DECLARE_APP(MyApp)
 
#endif // INCLUDED_MYAPP_H