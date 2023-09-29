using HMEditor.Game.Utilities;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;

namespace HMEditor.Game
{
    [DataContract]
    public class ProjectTemplete
    {
        [DataMember]
        public string? ProjectType { get; set; }
        [DataMember]
        public string? ProjectFile { get; set; }
        [DataMember]
        public List<string>? Folders { get; set; }

        public byte[]? Icon { get; set; }
        public byte[]? Screenshot { get; set; }
        public string? IconFilePath { get; set; }
        public string? ScreenshotFilePath { get; set; }
        public string? ProjectFilePath { get; set; }
    }

    public class CreateProject : ViewModelBase
    {
        // TODO : get the path from the installation location
        private readonly string mTemplatePath = @"..\..\HMEditor\ProjectTemplates";
        private string mProjectName = "NewProject";
        public string ProjectName
        {
            get => mProjectName;
            set
            {
                mProjectName = value;
                OnPropertyChanged(nameof(mProjectName));
            }
        }

        private string mProjectPath = $@"{Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments)}\HMEngine\";
        public string ProjectPath
        {
            get => mProjectPath;
            set
            {
                mProjectPath = value;
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
                string[] templatesFiles = Directory.GetFiles(mTemplatePath, "template.xml", SearchOption.AllDirectories);
                Debug.Assert(templatesFiles.Any());
                foreach(string file in templatesFiles)
                {
                    ProjectTemplete template = Serializer.FromFile<ProjectTemplete>(file);
                    string? directoryPath = Path.GetDirectoryName(file);
                    if(directoryPath == null || template.ProjectFile == null)
                    {
                        Debug.WriteLine("DirectoryName is Null");
                        return;
                    }
                    template.IconFilePath = Path.GetFullPath(Path.Combine(directoryPath, "icon.png"));
                    template.Icon = File.ReadAllBytes(template.IconFilePath);
                    template.ScreenshotFilePath = Path.GetFullPath(Path.Combine(directoryPath, "Screenshot.png"));
                    template.Screenshot = File.ReadAllBytes(template.ScreenshotFilePath);
                    template.ProjectFilePath = Path.GetFullPath(Path.Combine(directoryPath, template.ProjectFile));

                    mProjectTemplates.Add(template);
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
