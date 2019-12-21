using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;

namespace Project3
{
  /// <summary>
  /// Interaction logic for App.xaml
  /// </summary>
  public partial class App : Application
  {
        //----< called as application starts up >------------------------

        private void Application_Startup(object sender, StartupEventArgs e)
        {
            Project3.MainWindow mwin = new Project3.MainWindow();
            if (e.Args.Length >= 1)
            {
                if (e.Args[0] == "test")
                {
                    bool result = mwin.test();
                    Console.Write("\n  command line test passed");
                    mwin.tran.convert(mwin.path, mwin.convertedPath, true, true, true);

                    if (mwin.convertedFiles.Any())
                    {
                        mwin.tran.demonstrate(mwin.convertedFiles);
                    }
                } 
            }
        }
    }
}
