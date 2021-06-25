using System;
using System.ComponentModel;
using System.IO;
using System.Net;
using System.Diagnostics;
using System.Threading;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using System.IO.Compression;
using System.Collections.Concurrent;


namespace Hazel{
	class Setup{
		public static void Main(string[] args){
			Console.WriteLine("Welcome!");
			Console.WriteLine("Please wait while make everything ready for you to get started with Hazel!");
			Console.WriteLine("");
			VulkanResolver.ValidateAndResolve();
			Console.WriteLine("Press any key to continue.");
			Console.ReadLine();
		}

		
	}

	class VulkanResolver{
		private static readonly string m_RequiredVulkanVersion = "1.2.170.0";
		private static readonly string m_VulkanDirectory = @"../Hazel/vendor/VulkanSDK";

		public static bool ValidateAndResolve(){
			bool sdk = false;
			bool lib = false;
			string vulkanSDK = Environment.GetEnvironmentVariable("VULKAN_SDK");
			if (vulkanSDK == null){
				Console.WriteLine("\nYou don't have the Vulkan SDK installed!");
				sdk = InstallVulkanSDK(m_RequiredVulkanVersion);
			}	
			else{
				Console.WriteLine("\nLocated Vulkan SDK at " + vulkanSDK +  " .");
			}

			if (vulkanSDK.IndexOf(m_RequiredVulkanVersion) == -1){
				Console.WriteLine("You don't have the correct Vulkan SDK version! (Engine requires " + m_RequiredVulkanVersion + ")");
				sdk = InstallVulkanSDK(m_RequiredVulkanVersion);
			}else{
				Console.WriteLine("Correct Vulkan SDK located at " + vulkanSDK + " .");
			}

			string shadercdLib = m_VulkanDirectory + @"/Lib/shaderc_sharedd.lib";

			if(!File.Exists(shadercdLib)){
				Console.WriteLine("\nNo Vulkan SDK debug libs found. (Checked " + shadercdLib + ")");
				string vulkanPath = m_VulkanDirectory + @"/VulkanSDK-" + m_RequiredVulkanVersion + @"-DebugLibs.zip";
				if(!Utils.ShowConfirmation("Do you want to download the VulkanDebugLibs( ~ 400 MB )")){
					return false;
				}
				lib = GetVulkanLibs(vulkanPath, m_VulkanDirectory);
				Console.WriteLine("Vulkan SDK debug libs installed at " + m_VulkanDirectory);
			}
			else{
				Console.WriteLine("\nVulkan SDK debug libs located at " + m_VulkanDirectory);
			}
			return sdk && lib;
		}

		public static bool InstallVulkanSDK(string version){
			if(!Utils.ShowConfirmation("Do you want to download the VulkanSDK( ~ 250 MB )")){
				return false;
			}
			if(FileDownloader.DownloadFile("https://sdk.lunarg.com/sdk/download/" + version + "/windows/VulkanSDK-" + version + "-Installer.exe", @"./VulkanSDK.exe", 5000)){
				Process process = Process.Start(Path.GetFullPath(@"./VulkanSDK.exe"));
				process.WaitForExit();
				Console.WriteLine("After Installing VulkanSDK re-run this program!");
				return false;
			}else{
				Console.WriteLine("Failed to download Vulkan SDK!");
				return false;
			}
		}

		public static bool GetVulkanLibs(string path, string dir){
			string[] VulkanSDKDebugLibsURLlist = {
				"https://sdk.lunarg.com/sdk/download/" + m_RequiredVulkanVersion + "/windows/VulkanSDK-" + m_RequiredVulkanVersion + "-DebugLibs.zip",
				"https://files.lunarg.com/SDK-" + m_RequiredVulkanVersion + "/VulkanSDK-" + m_RequiredVulkanVersion + "-DebugLibs.zip"
			};
			if(FileDownloader.DownloadFile(VulkanSDKDebugLibsURLlist[0], path, 5000)){
				Console.WriteLine("Please wait while the files are being extracted...");
				if(Utils.UnZip(path, dir))
					Console.WriteLine("Sucessfully Exctracted \"" + Path.GetFullPath(path) + "\" to \"" + Path.GetFullPath(dir) + "\"");
			}else{
				Console.WriteLine("Failed to download Vulkan Libs!");
				return false;
			}
			return true;
		}
	}

	class FileDownloader
	{
		private SemaphoreSlim m_Sem = new SemaphoreSlim(0, Int32.MaxValue); 
		private readonly string m_Url;
		private readonly string m_FullPathWhereToSave;
		private bool m_Result = false, m_IsComp;
		private DateTime m_StartedAt;

		public FileDownloader(string url, string fullPathWhereToSave)
		{
			if (string.IsNullOrEmpty(url)) throw new ArgumentNullException("url");
			if (string.IsNullOrEmpty(fullPathWhereToSave)) throw new ArgumentNullException("fullPathWhereToSave");

			this.m_Url = url;
			this.m_FullPathWhereToSave = fullPathWhereToSave;
		}

		public bool StartDownload(int timeout)
		{
			try
			{
				m_IsComp = false;
				System.IO.Directory.CreateDirectory(Path.GetDirectoryName(m_FullPathWhereToSave));

				if (File.Exists(m_FullPathWhereToSave))
				{
					File.Delete(m_FullPathWhereToSave);
				}
				using (WebClient client = new WebClient())
				{
					var ur = new Uri(m_Url);
					client.DownloadProgressChanged += WebClientDownloadProgressChanged;
					client.DownloadFileCompleted += WebClientDownloadCompleted;
					Console.WriteLine(@"Downloading file:");
					client.DownloadFileAsync(ur, m_FullPathWhereToSave);
					m_Sem.Wait(Int32.MaxValue);
					Console.WriteLine("Your File Has Been Downloaded!");
					return m_Result && File.Exists(m_FullPathWhereToSave);
				}
			}
			catch (Exception)
			{
				Console.WriteLine("Was not able to download file!");
				return false;
			}
			finally{
				m_Sem.Release();
			}
		}

		private void WebClientDownloadProgressChanged(object sender, DownloadProgressChangedEventArgs e)
		{
			if (m_StartedAt == default(DateTime))
			{
				m_StartedAt = DateTime.Now;
			}
			else
			{
				var timeSpan = DateTime.Now - m_StartedAt;
				if (timeSpan.TotalSeconds > 0)
				{
					var kiloBytesPerSecond = (e.BytesReceived / timeSpan.TotalSeconds)/1024;
					if(kiloBytesPerSecond < 512){
						Console.Write("\rDownloaded: {0}%\t(Average speed: {1} KB/s) [Warning : Slow Connection Detected. (It will take a long time)]", e.ProgressPercentage, (kiloBytesPerSecond));						
					}else if(kiloBytesPerSecond < 1024){
						Console.Write("\rDownloaded: {0}%\t(Average speed: {1} KB/s)", e.ProgressPercentage, (kiloBytesPerSecond));							
					}else{
						Console.Write("\rDownloaded: {0}%\t(Average speed: {1} MB/s)", e.ProgressPercentage, (kiloBytesPerSecond/(1024)));							
					}
				}
			}
		}

		private void WebClientDownloadCompleted(object sender, AsyncCompletedEventArgs args)
		{
			m_Result = !args.Cancelled;
			if (!m_Result)
			{
				Console.Write("Failed to download file!");
			}
			m_IsComp = true;
			m_Sem.Release();
			Console.WriteLine(Environment.NewLine + "Download finished!");
		}

		public static bool DownloadFile(string url, string fullPathWhereToSave, int timeoutInMilliSec)
		{
			return new FileDownloader(url, fullPathWhereToSave).StartDownload(timeoutInMilliSec);
		}
	}

	class Utils{
		public static bool ShowConfirmation(string message){
			DialogResult ans = MessageBox.Show(message, "Confirm", MessageBoxButtons.YesNo, MessageBoxIcon.Question);
			if (ans == DialogResult.Yes)
			{
				return true;
			}
			else
			{
				return false;	
			}
			// OR 
			// return (ans == DialogResult.Yes);
		}


		public static bool UnZip(string zipPath, string extractPath)
		{
			zipPath = Path.GetFullPath(zipPath);
			extractPath = Path.GetFullPath(extractPath);
			try
            {
                using (Process process = new Process())
                {
                    process.StartInfo.FileName = Path.GetFullPath(@"./7z.exe");
                    process.StartInfo.WorkingDirectory = extractPath;
                    process.StartInfo.Arguments = "x -y \"" + zipPath + "\"";
                    process.Start();
                    process.WaitForExit();
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e + "\nError in extracting Zip. Please manually extract : " + Path.GetFullPath(zipPath) + " to " + Path.GetFullPath(extractPath) + " or re-run this!" );
                return false;
            }
return true;
		}
	}
}