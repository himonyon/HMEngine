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

namespace HMEditor.Game
{
    /// <summary>
    /// OpenProjectView.xaml の相互作用ロジック
    /// </summary>
    public partial class OpenProjectView : UserControl
    {
        public OpenProjectView()
        {
            InitializeComponent();
        }

        private void OnOpen_Button_Click(object sender, RoutedEventArgs e)
        {
            OpenSelectedProject();
        }

        private void OnListBoxItem_Mouse_DoubleClick(object sender, MouseButtonEventArgs e)
        {
            OpenSelectedProject();
        }

        private void OpenSelectedProject()
        {
            Project project = OpenProject.Open(projectsListBox.SelectedItem as ProjectData);
            bool dialogResult = false;
            Window win = Window.GetWindow(this);
            if (project != null)
            {
                dialogResult = true;
                win.DataContext = project;
            }
            win.DialogResult = dialogResult;
            win.Close();
        }
    }
}
