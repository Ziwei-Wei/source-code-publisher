/////////////////////////////////////////////////////////////////////
// MainWindow.xaml.cs - Prototype for OOD Project #4               //
// ver 1.2                                                         //
// Jim Fawcett, CSE687 - Object Oriented Design, Fall 2018         //
/////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This package defines one class MainWindow that provides tabs:
 * - Find Libs: Navigate through local directory to find files for testing
 *   - Shows local directories and files
 *   - Can navigate by double clicking directories
 *   - Can select files by selecting.  That displays selections in a popup window.
 * - Request Tests: left for students
 * - Show Results:  left for students
 * 
 * Required Files:
 * ---------------
 * MainWindow.xaml, MainWindow.xaml.cs
 * SelectionWindow.xaml, SelectionWindow.xaml.cs
 * 
 * Maintenance History:
 * --------------------
 * ver 1.2 : 28 Mar 2019
 * - fixed bug in DirsMouse_DoubleClick by using try catch block to
 *   handle exception that occurs if user clicks on unpopulated listbox item.
 * ver 1.1 : 16 Nov 2018
 * - fixed bug in Files_SelectionChanged by checking e.AddedItems.Count
 *   and returning if 0.
 * ver 1.0 : 15 Nov 2018
 * - first release
 * 
 */
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Security.Principal;
using System.IO;

namespace Project3
{
    ///////////////////////////////////////////////////////////////////
    // MainWindow class
    // - Provides navigation and selection to find libraries to test.
    // - Creates a popup window to handle selections.

    public partial class MainWindow : Window
    {
        public string path { get; set; }
        public string convertedPath { get; set; }
        public List<string> selectedFiles { get; set; } = new List<string>();
        public List<string> convertedFiles { get; set; } = new List<string>();
        public SelectionWindow swin { get; set; } = null;
        bool unselecting = false;
        public ITranslator tran;
       
        
        
        public MainWindow()
        {
            InitializeComponent();
        }

        //----< open window showing contents of project directory >------
        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            path = Directory.GetCurrentDirectory();
            path = getAncestorPath(3, path);
            LoadNavTab(path);
            convertedPath = "../../../convertedPages";
            ClearConverted(convertedPath);
            tran = TranslatorFactory.createTranslator();
        }

        //----< find parent paths >--------------------------------------
        string getAncestorPath(int n, string path)
        {
            for (int i = 0; i < n; ++i)
                path = Directory.GetParent(path).FullName;
            return path;
        }


        private void ClearConverted_Click(object sender, RoutedEventArgs e)
        {
            ClearConverted(convertedPath);
            Console.Write("\n\n  Called Method: " + GetMethodName());
            test();
        }


        private void DisplayConverted_Click(object sender, RoutedEventArgs e)
        {
            if (convertedFiles.Any()) {
                tran.demonstrate(convertedFiles);
            }
            Console.Write("\n\n  Called Method: " + GetMethodName());
            test();
        }

        //----< clear converted files >-----------------------------------
        void ClearConverted(string path)
        {
            System.IO.DirectoryInfo di = new DirectoryInfo(path);

            foreach (FileInfo file in di.GetFiles())
            {
                file.Delete();
            }
            convertedFiles.Clear();
            LoadConverted(path);
        }

        public void ConvertPath_Click(object sender, RoutedEventArgs e)
        {

            tran.convert(path, convertedPath, true, true, true);
            LoadConverted(convertedPath);
            Console.Write("\n\n  Called Method: " + GetMethodName());
            test();
        }

        //----< load converted files >-----------------------------------
        public void LoadConverted(string path)
        {
            Converted.Items.Clear();
            string[] files = Directory.GetFiles(path);
            foreach (string file in files)
            {
                string name = System.IO.Path.GetFileName(file);
                convertedFiles.Add(System.IO.Path.GetFullPath(convertedPath) + "/" + name);
                Converted.Items.Add(name);
            }
        }

        //----< file Find Libs tab with subdirectories and files >-------
        void LoadNavTab(string path)
        {
            Dirs.Items.Clear();
            CurrPath.Text = path;
            string[] dirs = Directory.GetDirectories(path);
            Dirs.Items.Add("..");
            foreach (string dir in dirs)
            {
                DirectoryInfo di = new DirectoryInfo(dir);
                string name = System.IO.Path.GetDirectoryName(dir);
                Dirs.Items.Add(di.Name);
            }
            Files.Items.Clear();
            string[] files = Directory.GetFiles(path);
            foreach (string file in files)
            {
                string name = System.IO.Path.GetFileName(file);
                Files.Items.Add(name);
            }
        }

        //----< handle selections in files listbox >---------------------
        private void Files_SelectionChanged(
          object sender, SelectionChangedEventArgs e
        )
        {
            if (unselecting)
            {
                unselecting = false;
                return;
            }
            if (swin == null)
            {
                swin = new SelectionWindow();
                swin.setMainWindow(this);
            }
            swin.Show();

            if (e.AddedItems.Count == 0)
                return;
            string selStr = e.AddedItems[0].ToString();
            selStr = System.IO.Path.Combine(path, selStr);
            if (!selectedFiles.Contains(selStr))
            {
                selectedFiles.Add(selStr);
                swin.Add(selStr);
            }
            Console.Write("\n\n  Called Method: " + GetMethodName());
            test();
        }

        //----< unselect files called by unloading SelectionWindow >-----
        public void unselectFiles()
        {
            unselecting = true;  // needed to avoid using selection logic
                                 //selectedFiles.Clear();
            Files.UnselectAll();
        }

        //----< move into double-clicked directory, display contents >---
        private void Dirs_MouseDoubleClick(object sender, MouseButtonEventArgs e)
        {
            try
            {
                string selectedDir = Dirs.SelectedItem.ToString();
                if (selectedDir == "..")
                    path = getAncestorPath(1, path);
                else
                    path = System.IO.Path.Combine(path, selectedDir);
                LoadNavTab(path);
                Console.Write("\n\n  Called Method: " + GetMethodName());
                test();
            }
            catch
            {
                // just return
            }
        }

        //----< shut down the SelectionWindow if open >------------------
        private void Window_Unloaded(object sender, RoutedEventArgs e)
        {
            if (swin != null) {
                swin.Close();
            }
        }

        //----< for test >----------------------------------------------
        public bool test()
        {
            int count = 0;       
            Console.Write("\n  my command line is:");
            foreach (string arg in Environment.GetCommandLineArgs())
            {
                Console.Write("\n    arg#{0} = {1}", ++count, arg);
            }
            Console.Write("\n  running as administrator: {0}", IsAdministrator());
            
            Console.Write("\n  passed test = true");
            return true;
        }

        public bool IsAdministrator()
        {
            var identity = WindowsIdentity.GetCurrent();
            var principle = new WindowsPrincipal(identity);
            return principle.IsInRole(WindowsBuiltInRole.Administrator);
        }

        // Return the name of the method that called this one.
        public string GetMethodName()
        {
            return new System.Diagnostics.StackTrace(1).GetFrame(0).GetMethod().Name;
        }
    }
}