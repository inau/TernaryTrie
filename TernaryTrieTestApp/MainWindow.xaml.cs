using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
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

namespace TernaryTrieTestApp
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        IntPtr _trie 
            = IntPtr.Zero;
        IntPtr _result
            = IntPtr.Zero;
        IntPtr _cancel
            = IntPtr.Zero;


        public MainWindow()
        {
            InitializeComponent();

            _trie = CppDLL.Trie.CreateTrieObject();
            _result = CppDLL.Result.CreateResultObject();
        }

        List<String> stringsFromFile = new List<string>();
        ObservableCollection<String> stringsFromSearch = new ObservableCollection<string>();
        private void Button_Click(object sender, RoutedEventArgs e) // load
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            if (openFileDialog.ShowDialog() == true)
            {
                foreach(var str in File.ReadLines(openFileDialog.FileName))
                {
                    stringsFromFile.Add(str);
                    CppDLL.Trie.Add(_trie, str);
                }
                FileListView.ItemsSource = stringsFromFile;

                uint trieSize = CppDLL.Trie.Size(_trie);
                System.Diagnostics.Trace.WriteLine($"Read {stringsFromFile?.Count ?? 0} from file, added {trieSize} to trie");
            }
        }

        private void Button_Click_1(object sender, RoutedEventArgs e) // search
        {
            if(!RealtimeSearchCB?.IsChecked ?? false)
            {
                SearchFor(searchQueryText.Text);
                FileListViewFiltered.ItemsSource = stringsFromSearch;
            }
        }

        private void TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (RealtimeSearchCB?.IsChecked ?? false)
            {
                SearchFor(searchQueryText.Text);
                FileListViewFiltered.ItemsSource = stringsFromSearch;
                
            }
        }

        CancellationTokenSource cancelTokenSource 
            = new CancellationTokenSource();
        Task? currentSearch
            = null;
        public void SearchFor(String text)
        {
            stringsFromSearch.Clear();
        
            CppDLL.Trie.Search(_trie, text, _result, _cancel);

            uint cnt = CppDLL.Result.getResultSize(_result);
            for (uint i = 0; i < cnt; ++i)
            {
               IntPtr element = CppDLL.Result.getResultElement(_result, i);
               IntPtr txt = CppDLL.Result.ItemGetText(element);
               string str = Marshal.PtrToStringAnsi(txt);
               stringsFromSearch.Add(str);
            }


           // cancelTokenSource.Cancel();
           //
           // currentSearch = new Task(
           //     () => 
           //     {
           //         
           //     }, 
           //     cancelTokenSource.Token
           // );
        }
    }
}
