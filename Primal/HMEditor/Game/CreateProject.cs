using HMEditor.Game.Utilities;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Windows.Media.Animation;

namespace HMEditor.Game
{
    [DataContract]
    public class ProjectTemplete
    {
        [DataMember]
        public string ProjectType { get; set; }
        [DataMember]
        public string ProjectFile { get; set; }
        [DataMember]
        public List<string> Folders { get; set; }
    }

    public class CreateProject : ViewModelBase
    {
        // TODO : get the path from the installation location
        private readonly string mTemplatePath = @"..\..\HMEditor\ProjectTemplates";
        private string mName = "NewProject";
        public string Name
        {
            get => mName;
            set
            {
                mName = value;
                OnPropertyChanged(nameof(Name));
            }
        }

        private string mPath = $@"{Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments)}\HMEngine\";
        public string Path
        {
            get => mPath;
            set
            {
                mPath = value;
                OnPropertyChanged(nameof(Path));
            }
        }

        private ObservableCollection<ProjectTemplete> mProjectTemplates = new ObservableCollection<ProjectTemplete>();
        public ReadOnlyObservableCollection<ProjectTemplete> ProjectTemplates { get; }

        public CreateProject()
        {
            ProjectTemplates = new ReadOnlyObservableCollection<ProjectTemplete>(mProjectTemplates);
            try
            {
                string[] templatesFIles = Directory.GetFiles(mTemplatePath, "template.xml", SearchOption.AllDirectories);
                Debug.Assert(templatesFIles.Any());
                foreach(string file in templatesFIles)
                {
                    Serializer.FromFile<ProjectTemplete>(file);
                }
            }
            catch(Exception ex) 
            {
                Debug.WriteLine(ex.Message);
                //TODO : error log
            }
        }
    }
}
