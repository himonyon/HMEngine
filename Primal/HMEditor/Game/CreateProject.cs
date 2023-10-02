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
                ValidateProjectPath();
                OnPropertyChanged(nameof(mProjectName));
            }
        }

        private string mProjectPath = $@"{Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments)}\HMProjects\";
        public string ProjectPath
        {
            get => mProjectPath;
            set
            {
                mProjectPath = value;
                ValidateProjectPath();
                OnPropertyChanged(nameof(Path));
            }
        }

        private bool mIsValid = false;
        public bool IsValid
        {
            get => mIsValid;
            set
            {
                mIsValid = value;
                OnPropertyChanged(nameof(IsValid));
            }
        }

        private string mErrorMsg = "";
        public string ErrorMsg
        {
            get => mErrorMsg;
            set
            {
                mErrorMsg = value;
                OnPropertyChanged(nameof(ErrorMsg));
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
                ValidateProjectPath();
            }
            catch(Exception ex) 
            {
                Debug.WriteLine(ex.Message);
                //TODO : error log
            }
        }

        public string CreateNewProject(ProjectTemplete template)
        {
            ValidateProjectPath();
            if (!IsValid)
            {
                return string.Empty;
            }
            if (!Path.EndsInDirectorySeparator(ProjectPath)) ProjectPath += @"\";
            string path = $@"{ProjectPath}{ProjectName}\";

            try
            {
                if (!Directory.Exists(path)) Directory.CreateDirectory(path);
                if(template.Folders == null || template.Folders.Count == 0)
                {
                    return string.Empty;
                }
                foreach(string folder in template.Folders)
                {
                    Directory.CreateDirectory(Path.GetFullPath(Path.Combine(Path.GetDirectoryName(path), folder)));
                }
                DirectoryInfo directoryInfo = new DirectoryInfo(path + @".Hm\");
                directoryInfo.Attributes |= FileAttributes.Hidden;
                File.Copy(template.IconFilePath, Path.GetFullPath(Path.Combine(directoryInfo.FullName, "icon.png")));
                File.Copy(template.ScreenshotFilePath, Path.GetFullPath(Path.Combine(directoryInfo.FullName, "Screenshot.png")));

                Project newProject = new Project(ProjectName, path);
                Serializer.ToFIle(newProject, path + "ProjectName" + Project.Extension);
                return path;

                return "";
            }catch (Exception ex)
            {
                Debug.WriteLine(ex.ToString());
                return string.Empty;
            }
        }

        private bool ValidateProjectPath()
        {
            string path = ProjectPath;
            if (!Path.EndsInDirectorySeparator(path)) path += @"\";
            path += $@"{ProjectName}\";

            IsValid = false;
            if(string.IsNullOrWhiteSpace(ProjectName.Trim()))
            {
                ErrorMsg = "Type in a project name.";
            }else if(ProjectName.IndexOfAny(Path.GetInvalidFileNameChars()) != -1)
            {
                ErrorMsg = "Invalid characters used in project name";
            }
            else if (string.IsNullOrWhiteSpace(ProjectPath.Trim()))
            {
                ErrorMsg = "Select a valid project folder.";
            }
            else if (ProjectPath.IndexOfAny(Path.GetInvalidPathChars()) != -1)
            {
                ErrorMsg = "Invalid characters used in project path";
            }
            else if(Directory.Exists(path) && Directory.EnumerateFileSystemEntries(path).Any())
            {
                ErrorMsg = "Selected project folder already exists and is not empty";
            }
            else
            {
                ErrorMsg = string.Empty;
                IsValid = true;
            }
            return IsValid;
        }
    }
}
