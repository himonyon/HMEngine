using HMEditor.Game.Utilities;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.Serialization;
using System.Security.RightsManagement;
using System.Text;
using System.Threading.Tasks;

namespace HMEditor.Game
{
    [DataContract]
    public class ProjectData
    {
        [DataMember]
        public string ProjectName { get; set; }
        [DataMember]
        public string ProjectPath { get; set; }
        [DataMember]
        public DateTime Date { get; set; }

        public string FullPath { get => $"{ProjectPath}{ProjectName}{Project.Extension}"; }
        public byte[] Icon { get; set; }
        public byte[] Screenshot { get; set; }
    }

    [DataContract]
    public class ProjectDataList
    {
        [DataMember]
        public List<ProjectData> Projects { get; set; }
    }

    class OpenProject
    {
        private static readonly string mApplicationDataPath = $@"{Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData)}\HMEditor\";
        private static readonly string mProjectDataPath;
        private static readonly ObservableCollection<ProjectData> mProjects = new ObservableCollection<ProjectData>();

        public static ReadOnlyObservableCollection<ProjectData> Projects { get; }

        static OpenProject()
        {
            try
            {
                if(!Directory.Exists(mApplicationDataPath)) Directory.CreateDirectory(mApplicationDataPath);
                mProjectDataPath = $@"{mApplicationDataPath}ProjectData.xml";
                Projects = new ReadOnlyObservableCollection<ProjectData>(mProjects);
                ReadProjectData();
            }
            catch (Exception ex)
            {
                Debug.WriteLine(ex.Message);
                //TODO : error log
            }
        }

        public static Project Open(ProjectData data)
        {
            ReadProjectData();
            ProjectData project = mProjects.FirstOrDefault(x => x.FullPath == data.FullPath);
            if(project != null)
            {
                project.Date = DateTime.Now;
            }
            else
            {
                project = data;
                project.Date = DateTime.Now;
                mProjects.Add(project);
            }
            WriteProjectData();

            return Project.Load(project.FullPath);
        }

        private static void ReadProjectData()
        {
            if(File.Exists(mProjectDataPath))
            {
                IOrderedEnumerable<ProjectData> projects = Serializer.FromFile<ProjectDataList>(mProjectDataPath).Projects.OrderByDescending(x => x.Date);
                mProjects.Clear();
                foreach (ProjectData project in projects)
                {
                    if (File.Exists(project.FullPath))
                    {
                        project.Icon = File.ReadAllBytes($@"{project.ProjectPath}\.Hm\Icon.png");
                        project.Screenshot = File.ReadAllBytes($@"{project.ProjectPath}\.Hm\Screenshot.png");
                        mProjects.Add(project);
                    }
                }
            }
        }

        private static void WriteProjectData()
        {
            List<ProjectData> projects= mProjects.OrderBy(x => x.Date).ToList();
            Serializer.ToFile(new ProjectDataList() { Projects = projects }, mProjectDataPath);
        }
    }
}
