#include "ArtificialIntelligence.h"
#include <format>
#include <queue>
#include "../Platforms/CommandCentre.h"
#include "../utils/CheckComponent.h"
#include "../Platforms/MobilePlatform.h"
#include <algorithm>
#include "../Platforms/RobotCommander.h"
#include "../Interfaces/Destroying.h"
#include "../Platforms/RobotDestroyer.h"
#include <chrono>
#include <thread>

namespace Robots
{
	void Node::consoleOut(std::ostream& stream)
	{
		stream << std::format("({}, {}) type: {} isTraversable: {}", std::to_string(cell->getX()), std::to_string(cell->getY()), Field::CellTypeToString(cell->getType()), isTraversable) << std::endl;
	}

	void ArtificialIntelligence::consoleOutGraph(std::ostream& stream)
	{
		stream << "key | node" << std::endl;
		for (auto it : graph)
		{
			auto key = it.first;
			auto value = it.second;

			stream << std::format("({}, {}) | ({}, {}) type: {} isTraversable: {}", std::to_string(key.first), std::to_string(key.second), std::to_string(value.cell->getCoordinates().first), std::to_string(value.cell->getCoordinates().second), Field::CellTypeToString(value.cell->getType()), value.isTraversable) << std::endl;
		}
	}

	std::vector<Node*> ArtificialIntelligence::path(Field::Cell* from, Field::Cell* to, Field::Field& field)
	{
		auto cmp = [](Node* first, Node* second) {return first->f > second->f; };
		std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> openList(cmp);
		std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> closedList(cmp);
		std::vector<Node*> path;
		std::vector<Node*> obstacles;

		Node* start = &graph[from->getCoordinates()];
		Node* target = &graph[to->getCoordinates()];

		start->g = 0;
		start->h = Field::distance(from->getCoordinates(), to->getCoordinates());
		start->calculateF();
		openList.push(start);
		start->isOpen = true;

		while (!openList.empty())
		{
			//poping node with minimum f cost
			Node* current = openList.top();
			openList.pop();
			closedList.push(current);
			current->isOpen = false;
			current->isClosed = true;

			if (current == target)
			{
				Node* ptr = current;
				while (ptr != nullptr)
				{
					path.push_back(ptr);
					ptr = ptr->predecessor;
				}

				//cleaning nodes not in the path
				while(!openList.empty())
				{
					Node* unused = openList.top();
					openList.pop();
					cleanNode(unused);
				}

				while(!closedList.empty())
				{
					Node* mbused = closedList.top();
					closedList.pop();
					bool inPath = false;
					for (Node* nd : path)
					{
						if (nd == mbused)
						{
							inPath = true;
							break;
						}
					}
					if (!inPath) cleanNode(mbused);
				}
				return path;
			}

			//generating neighbours
			if (current->cell->getX() - 1 >= 0)
			{
				Node* neighbour = &graph[{current->cell->getX() - 1, current->cell->getY()}];
				//neighbour->g = current->g + 1;
				//neighbour->h = Field::distance(neighbour->cell->getCoordinates(), to->getCoordinates());
				current->neighbours.push_back(neighbour);
			}
			if (current->cell->getX() + 1 < field.getWidth())
			{
				Node* neighbour = &graph[{current->cell->getX() + 1, current->cell->getY()}];
				//neighbour->g = current->g + 1;
				//neighbour->h = Field::distance(neighbour->cell->getCoordinates(), to->getCoordinates());
				current->neighbours.push_back(neighbour);
			}
			if (current->cell->getY() - 1 >= 0)
			{
				Node* neighbour = &graph[{current->cell->getX(), current->cell->getY()-1}];
				//neighbour->g = current->g + 1;
				//neighbour->h = Field::distance(neighbour->cell->getCoordinates(), to->getCoordinates());
				current->neighbours.push_back(neighbour);
			}
			if (current->cell->getY() + 1 < field.getHeight())
			{
				Node* neighbour = &graph[{current->cell->getX(), current->cell->getY()+1}];
				//neighbour->g = current->g + 1;
				//neighbour->h = Field::distance(neighbour->cell->getCoordinates(), to->getCoordinates());
				current->neighbours.push_back(neighbour);
			}

			for (Node* neighbour : current->neighbours)
			{
				if (!neighbour->isTraversable || neighbour->isClosed)
				{
					if (!neighbour->isTraversable) obstacles.push_back(neighbour);
					continue;
				}
				else
				{
					int ng = current->g + 1;
					int nh = Field::distance(neighbour->cell->getCoordinates(), to->getCoordinates());
					if ((ng+nh) < neighbour->f || !neighbour->isOpen)
					{
						neighbour->g = ng;
						neighbour->h = nh;
						neighbour->predecessor = current;
						neighbour->calculateF();
						if (!neighbour->isOpen)
						{
							neighbour->isOpen = true;
							openList.push(neighbour);
						}
					}
					
				}
			}
		}

		//cleaning nodes not in the path
		while(!openList.empty())
		{
			Node* unused = openList.top();
			openList.pop();
			cleanNode(unused);
		}

		while(!closedList.empty())
		{
			Node* unused = closedList.top();
			closedList.pop();
			cleanNode(unused);
		}

		return obstacles;
	}

	void ArtificialIntelligence::cleanPath(std::vector<Node*>& path)
	{
		for (Node* node : path)
		{
			cleanNode(node);
		}
	}

	void ArtificialIntelligence::cleanNode(Node* node)
	{
		node->f = std::numeric_limits<int>::max();
		node->g = std::numeric_limits<int>::max();
		node->h = std::numeric_limits<int>::max();
		node->predecessor = nullptr;
		node->neighbours = std::vector<Node*>();
		node->isOpen = false;
		node->isClosed = false;
	}

	//some view functions
	void viewMove(std::string out, bool windowView = false, std::ostream& log = std::cout, Game::Drawer* dr=nullptr)
	{
		if (!windowView) log << out << std::endl;
		else
		{
			dr->generateErrorView(out);
		}
	}

	void viewField(Field::Field* fld, bool windowView = false, std::ostream& log = std::cout, Game::Drawer* dr=nullptr)
	{
		if (!windowView) fld->consoleOutField(log);
		else
		{
			dr->cleanViews();
			dr->views = std::vector<Game::View*>();
			dr->viewField(fld);
			for (Game::View* view : dr->views)
			{
				dr->window.draw(view->sprite);
			}
			dr->Ai->draw();
			dr->window.draw(dr->Ai->sprite);
			dr->window.draw(dr->Ai->description);
		}
	}

	int ArtificialIntelligence::parallel_rulling_decision(Field::Field& fld, Robots::Platform* plt, Robots::Platform* sub, bool& endOfGame)
	{
			//log << "sub name: " << sub->getName() << std::endl;
			//log << (fld.checkPlatformOnField(sub->getCoordinates()) == nullptr) << std::endl;
		bool isReachable = true;
		try
		{
			dynamic_cast<Robots::CommandCentre*>(plt)->getCpu().checkReachable(sub);
		}
		catch (std::invalid_argument)
		{
			if (dynamic_cast<Robots::RobotCommander*>(plt)->getCpu().getLastSub() != nullptr)
			{
				Robots::Platform* last_sub = dynamic_cast<Robots::RobotCommander*>(plt)->getCpu().getLastSub();
				if (last_sub->getRoboPriority() > sub->getRoboPriority())
				{
					std::string out = masterSwitchTarget(plt, last_sub, fld);
					viewMove(out);
					return 0;
				}
				else if (last_sub->getRoboPriority() == sub->getRoboPriority())
				{
					if (Field::distance(plt->getCoordinates(), last_sub->getCoordinates()) <= Field::distance(plt->getCoordinates(), sub->getCoordinates()))
					{
						std::string out = masterSwitchTarget(plt, last_sub, fld);
						viewMove(out);
						return 0;
					}
					else
					{
						isReachable = false;
						std::string out = masterSwitchTarget(plt, sub, fld);
						viewMove(out);
					}
				}
				else
				{
					isReachable = false;
					std::string out = masterSwitchTarget(plt, sub, fld);
					viewMove(out);

				}
			}
			else
			{
				isReachable = false;
				std::string out = masterSwitchTarget(plt, sub, fld);
				viewMove(out);
			}
		}
		if (isReachable)
		{
			std::vector<Field::Cell> report = dynamic_cast<Robots::CommandCentre*>(plt)->getCpu().getReport(&fld, sub);

			//updating clone map
			for (Field::Cell cell : report)
			{
				cloneMap[cell.getX()][cell.getY()].setType(cell.getType());
			}


			std::string out = makeMove(*sub, fld, report);
			viewMove(out);
		}
		viewField(&fld);
		if (fld.total_poi == 0)
		{
			if(!endOfGame) endOfGame = true;
		}
		return 0;
		//std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	void ArtificialIntelligence::find_parallel(Field::Field& fld, bool windowView, std::ostream& log, Game::Drawer* dr)
	{
		cloneMap = std::vector<std::vector<Field::Cell>>(fld.getWidth());
		for (int i = 0; i < fld.getWidth(); i++)
		{
			//cloneMap[i] = std::vector<Field::Cell>();
			for (int j = 0; j < fld.getHeight(); j++)
			{
				cloneMap[i].push_back(Field::Cell(i, j, Field::CellType::unknown));
			}
		}

		std::vector<Robots::Platform*> rulling;
		for (auto pt : fld.getPlatforms())
		{
			if(pt.second->getIsMaster()) rulling.push_back(pt.second);
		}
		bool endOfGame = false;
		while (fld.total_poi != 0)
		{
			auto map = fld.getPlatforms();
			for (auto plt : rulling)
			{
				if (dynamic_cast<Robots::CommandCentre*>(plt)->getCpu().getSubOrd().size() != 0 && dynamic_cast<Robots::CommandCentre*>(plt)->getCpu().getLastSub() == nullptr) dynamic_cast<Robots::CommandCentre*>(plt)->getCpu().setLastSub(dynamic_cast<Robots::CommandCentre*>(plt)->getCpu().getSubOrd()[0]);
				if (dynamic_cast<Robots::CommandCentre*>(plt)->getCpu().getSubOrd().size() != 0)
				{
					std::size_t qouta = std::thread::hardware_concurrency();
					std::vector<std::thread> threads(qouta);
					for (int i = 0; i < dynamic_cast<Robots::CommandCentre*>(plt)->getCpu().getSubOrd().size(); i++)
					{
						Robots::Platform* sub = dynamic_cast<Robots::CommandCentre*>(plt)->getCpu().getSubOrd()[i];
						threads[i] = std::thread(&ArtificialIntelligence::parallel_rulling_decision, this, std::ref(fld), plt, sub, std::ref(endOfGame));
					}
					for (int j=0; j< dynamic_cast<Robots::CommandCentre*>(plt)->getCpu().getSubOrd().size(); j++)
					{
						threads[j].join();
					}
					//if(dynamic_cast<Robots::CommandCentre*>(plt)->getCpu().getSubOrd().size()!=0) exit(0);
					if (endOfGame)
					{
						break;
					}
				}
				
				if (dynamic_cast<Robots::CommandCentre*>(plt)->getCpu().getSubOrd().size() < dynamic_cast<Robots::CommandCentre*>(plt)->getCpu().getSub())
				{
					int min_dist = std::numeric_limits<int>::max();
					Robots::Platform* potentialSubord;
					for (auto itr : map)
					{
						Robots::Platform* robo = itr.second;
						if (robo != plt)
						{
							if ((Field::distance(plt->getCoordinates(), robo->getCoordinates()) < min_dist))
							{
								min_dist = Field::distance(plt->getCoordinates(), robo->getCoordinates());
								potentialSubord = robo;
							}
						}
					}
					if (potentialSubord->getMaster() == nullptr)
					{
						std::string out = masterSwitchTarget(plt, potentialSubord, fld);
						viewMove(out);
					}
				}
			}
		}
	}

	void ArtificialIntelligence::find(Field::Field& fld, bool windowView, std::ostream& log, Game::Drawer* dr)
	{
		cloneMap = std::vector<std::vector<Field::Cell>>(fld.getWidth());
		for (int i = 0; i < fld.getWidth(); i++)
		{
			//cloneMap[i] = std::vector<Field::Cell>();
			for (int j = 0; j < fld.getHeight(); j++)
			{
				cloneMap[i].push_back(Field::Cell(i, j, Field::CellType::unknown));
			}
		}


		bool gameEnd = false;
		while (fld.total_poi != 0)
		{
			int size = fld.getPlatforms().size();
			auto map = fld.getPlatforms();
			for(auto& it : map)
			{
				if (gameEnd) break;
				//if (it == fld.getPlatforms().end()) std::cout << "END" << std::endl;
				if (size == 0) break;
				size--;
				Robots::Platform* plt = it.second;
				if (plt->getIsMaster())
				{
					
					
					if(dynamic_cast<Robots::CommandCentre*>(plt)->getCpu().getSubOrd().size()!=0 && dynamic_cast<Robots::CommandCentre*>(plt)->getCpu().getLastSub()==nullptr) dynamic_cast<Robots::CommandCentre*>(plt)->getCpu().setLastSub(dynamic_cast<Robots::CommandCentre*>(plt)->getCpu().getSubOrd()[0]);
					for (Robots::Platform* sub : dynamic_cast<Robots::CommandCentre*>(plt)->getCpu().getSubOrd())
					{
						//log << "sub name: " << sub->getName() << std::endl;
						//log << (fld.checkPlatformOnField(sub->getCoordinates()) == nullptr) << std::endl;
						bool isReachable = true;
						try
						{
							dynamic_cast<Robots::CommandCentre*>(plt)->getCpu().checkReachable(sub);
						}
						catch (std::invalid_argument)
						{
							if (dynamic_cast<Robots::RobotCommander*>(plt)->getCpu().getLastSub() != nullptr)
							{
								Robots::Platform* last_sub = dynamic_cast<Robots::RobotCommander*>(plt)->getCpu().getLastSub();
								//std::cout << "last sub: " << last_sub->getName()<<" "<<std::format("({}, {}) ", std::to_string(last_sub->getCoordinates().first), std::to_string(last_sub->getCoordinates().second)) << (int)last_sub->getRoboPriority() << std::endl;
								//std::cout << "sub: " << sub->getName()<<" "<<std::format("({}, {}) ", std::to_string(sub->getCoordinates().first), std::to_string(sub->getCoordinates().second)) << (int)sub->getRoboPriority() << std::endl;
								if (last_sub->getRoboPriority() > sub->getRoboPriority())
								{
									//std::cout << "db1" << std::endl;
									std::string out = masterSwitchTarget(plt, last_sub, fld);
									viewMove(out, windowView, log, dr);
									continue;
								}
								else if (last_sub->getRoboPriority() == sub->getRoboPriority())
								{
									if (Field::distance(plt->getCoordinates(), last_sub->getCoordinates()) <= Field::distance(plt->getCoordinates(), sub->getCoordinates()))
									{
										//std::cout << "db2" << std::endl;
										std::string out = masterSwitchTarget(plt, last_sub, fld);
										viewMove(out, windowView, log, dr);
										/*if (!Field::inArea(plt->getCoordinates(), last_sub->getCoordinates(), dynamic_cast<Robots::CommandCentre*>(plt)->getCpu().getRad()))
										{
											log<<goToTarget(*plt, fld.getCellByCoordinates(last_sub->getCoordinates()), fld)<<std::endl;
										}*/
										continue;
									}
									else
									{
										//std::cout << "db3" << std::endl;

										isReachable = false;
										std::string out = masterSwitchTarget(plt, sub, fld);
										viewMove(out, windowView, log, dr);
									}
								}
								else
								{
									//std::cout << "db4" << std::endl;

									isReachable = false;
									std::string out = masterSwitchTarget(plt, sub, fld);
									viewMove(out, windowView, log, dr);
									
								}
							}
							else
							{
								//std::cout << "db5" << std::endl;

								isReachable = false;
								std::string out = masterSwitchTarget(plt, sub, fld);
								viewMove(out, windowView, log, dr);
							}
						}
						if (isReachable)
						{
							//std::cout << "db6" << std::endl;

							std::vector<Field::Cell> report = dynamic_cast<Robots::CommandCentre*>(plt)->getCpu().getReport(&fld, sub);

							//updating clone map
							for (Field::Cell cell : report)
							{
								cloneMap[cell.getX()][cell.getY()].setType(cell.getType());
							}


							std::string out = makeMove(*sub, fld, report);
							viewMove(out, windowView, log, dr);
						}
						if (windowView) dr->window.clear();
						viewField(&fld, windowView, log, dr);
						if (windowView)
						{
							dr->window.draw(dr->tmp->description);
							dr->window.display();
							//std::this_thread::sleep_for(std::chrono::milliseconds(1200));
						}
						//fld.consoleOutField(log);
						log << std::endl;
						if (fld.total_poi == 0)
						{
							gameEnd = true;
							break;
						}
					}
					log << std::endl;
					//fld.consoleOutField();
					/*log << dynamic_cast<Robots::CommandCentre*>(plt)->getCpu().getSub() << std::endl;
					for (auto it : fld.getPlatforms())
					{
						it.second->consoleOut();
					}*/
					if (dynamic_cast<Robots::CommandCentre*>(plt)->getCpu().getSubOrd().size()< dynamic_cast<Robots::CommandCentre*>(plt)->getCpu().getSub())
					{
						int min_dist = std::numeric_limits<int>::max();
						Robots::Platform* potentialSubord;
						for (auto itr : map)
						{
							Robots::Platform* robo = itr.second;
							if (robo != plt)
							{
								if ((Field::distance(plt->getCoordinates(), robo->getCoordinates()) < min_dist))
								{
									min_dist = Field::distance(plt->getCoordinates(), robo->getCoordinates());
									potentialSubord = robo;
								}
							}
						}
						if (potentialSubord->getMaster() == nullptr)
						{
							std::string out=masterSwitchTarget(plt, potentialSubord, fld);
							viewMove(out, windowView, log, dr);
						}
					}
				
				}
				
			}
		}
		if (windowView)
		{
			dr->generateErrorView("AI won!", Game::Drawer::AI_WON_TEXTURE);
			dr->window.draw(dr->tmp->sprite);
			dr->window.display();
			while (dr->window.isOpen())
			{
				sf::Event event;
				while (dr->window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed) dr->window.close();
				}
			}
		}
		
	}

	

	std::string ArtificialIntelligence::makeMove(Robots::Platform& plt, Field::Field& fld, std::vector<Field::Cell>& targets, std::pair<int, int> specific_target)
	{
		std::cout << "total poi: " << fld.total_poi << std::endl;
		int old_total_poi = fld.total_poi;
		for (Field::Cell& target : targets)
		{
			if (target.getType() == Field::CellType::pointOfInterest && !plt.getIsMaster())
			{
				std::string log = goToTarget(plt, target, fld);
				if (log == "no path") continue;
				if (old_total_poi > fld.total_poi) addPoint();
				return log;
			}
			else if (plt.getIsMaster() && fld.checkPlatformOnField(target.getCoordinates()) != nullptr)
			{
				if (target.getCoordinates() == specific_target)
				{
					std::string log = goToTarget(plt, target, fld);
					if (log == "no path") continue;
					if (old_total_poi > fld.total_poi) addPoint();

					return log;
				}
			}
			else if (isComponentCastable<Robots::Platform&, Robots::Destroying&>(plt) && target.getType() == Field::CellType::obstacle)
			{
				bool isDestroyed = true;
				try
				{
					dynamic_cast<Robots::RobotDestroyer&>(plt).getGun().destroy(&fld, target.getCoordinates());
				}
				catch (std::invalid_argument)
				{
					isDestroyed = false;
					std::string log = goToTarget(plt, target, fld);
					if (log == "no path") continue;
					if (old_total_poi < fld.total_poi) addPoint();

					return log;
				}
				if (isDestroyed)
				{
					graph[target.getCoordinates()].isTraversable = true;
					cloneMap[target.getX()][target.getY()].setType(Field::CellType::ground);
				}
				std::string log = std::format("{} succesfully destroyed ({}, {})", plt.getName(), std::to_string(target.getX()), std::to_string(target.getY()));
				if (old_total_poi > fld.total_poi) addPoint();

				return log;
			}
		}
		
		if (!plt.getIsMaster() && fld.total_poi!=0)
		{
			
			for (std::vector<Field::Cell> row : cloneMap)
			{
				for (Field::Cell cell : row)
				{
					if (cell.getType() == Field::CellType::unknown || cell.getType()==Field::CellType::pointOfInterest)
					{
						//std::cout << "current unknown target: ";
						//cell.consoleOut();
						std::vector<Node*> pth = path(&fld.getCellByCoordinates(plt.getCoordinates()), &fld.getCellByCoordinates(cell.getCoordinates()), fld);
						std::reverse(pth.begin(), pth.end());
						if (pth[0]->isTraversable)
						{
							if (pth.size() == 1)
							{
								cloneMap[plt.getCoordinates().first][plt.getCoordinates().second].setType(fld.getCellByCoordinates(plt.getCoordinates()).getType());
								continue;
							}
							Field::Cell* closest_cell = pth[1]->cell;
							std::pair<int, int> old_coordinates = plt.getCoordinates();
							int i = 2;
							while (1)
							{
								try
								{
									fld.movePlatform(plt.getCoordinates(), { closest_cell->getX() - plt.getCoordinates().first, closest_cell->getY() - plt.getCoordinates().second });
								}
								catch (std::invalid_argument)
								{
									closest_cell = pth[i]->cell;
									i++;
									continue;
								}
								break;
							}
							cleanPath(pth);
							std::string log = std::format("{} moved from ({}, {}) to ({}, {})", plt.getName(), std::to_string(old_coordinates.first), std::to_string(old_coordinates.second), std::to_string(closest_cell->getX()), std::to_string(closest_cell->getY()));
							if (old_total_poi < fld.total_poi) addPoint();

							return log;
						}
						else
						{
							std::cout << "No path to this unknown cell exists: ";
							cell.consoleOut();

						}
					}
				}
			}
			std::cout << "No unknown target for " <<plt.getName() <<" found." << std::endl;
			std::cout << "poi now: " << fld.total_poi << std::endl;
			std::vector<Robots::Platform> emptyPlt;
			Field::Field tmp = Field::Field(fld.getWidth(), fld.getHeight(), cloneMap, emptyPlt);
			tmp.consoleOutField();
			exit(0);
		}
		return "boba";
	}

	std::string ArtificialIntelligence::masterSwitchTarget(Robots::Platform* plt, Robots::Platform* sub, Field::Field& fld)
	{
		if (Field::inArea(plt->getCoordinates(), sub->getCoordinates(), dynamic_cast<Robots::CommandCentre*>(plt)->getCpu().getRad()) && sub->getMaster()==nullptr)
		{
			if (dynamic_cast<Robots::CommandCentre*>(plt)->getCpu().getSubOrd().size() < dynamic_cast<Robots::CommandCentre*>(plt)->getCpu().getSub())
			{
				dynamic_cast<Robots::CommandCentre*>(plt)->getCpu().subdue(*sub);
				dynamic_cast<Robots::CommandCentre*>(plt)->getCpu().setLastSub(sub);
				return std::format("{} succesfully subdued {}", plt->getName(), sub->getName());
			}
			else
			{
				for (Robots::Platform* subord : dynamic_cast<Robots::CommandCentre*>(plt)->getCpu().getSubOrd())
				{
					if (subord->getRoboPriority() < sub->getRoboPriority())
					{
						dynamic_cast<Robots::CommandCentre*>(plt)->getCpu().release(subord);
						dynamic_cast<Robots::CommandCentre*>(plt)->getCpu().subdue(*sub);
						dynamic_cast<Robots::CommandCentre*>(plt)->getCpu().setLastSub(sub);
						return std::format("{} succesfully released {}.\n {} succesfully subdued {}.", plt->getName(), subord->getName(), plt->getName(), sub->getName());
					}
				}
			}
			return "cant subdue";
		}
		else
		{
			std::vector<Field::Cell> pseudo_report;
			pseudo_report.push_back(fld.getCellByCoordinates(sub->getCoordinates()));
			std::string out = makeMove(*plt, fld, pseudo_report, sub->getCoordinates());
			dynamic_cast<Robots::CommandCentre*>(plt)->getCpu().setLastSub(sub);
			return out;
		}
	}

	std::string ArtificialIntelligence::goToTarget(Robots::Platform& plt, Field::Cell& target, Field::Field& fld)
	{
		std::vector<Node*> pth = path(&fld.getCellByCoordinates(plt.getCoordinates()), &target, fld);
		std::reverse(pth.begin(), pth.end());

		if (!pth[0]->isTraversable)
		{
			return "no path";
		}
		Field::Cell* closest_cell = pth[1]->cell;
		std::pair<int, int> old_coordinates = plt.getCoordinates();
		int i = 2;
		while (1)
		{
			try
			{
				fld.movePlatform(plt.getCoordinates(), { closest_cell->getX() - plt.getCoordinates().first, closest_cell->getY() - plt.getCoordinates().second });
			}
			catch (std::invalid_argument)
			{
				if (i == pth.size())
				{
					cleanPath(pth);
					return "No path";
				}
				closest_cell = pth[i]->cell;
				i++;
				continue;
			}
			break;
		}
		//if (i == pth.size()) return "No path";
		std::string log = std::format("{} moved from ({}, {}) to ({}, {})", plt.getName(), std::to_string(old_coordinates.first), std::to_string(old_coordinates.second), std::to_string(closest_cell->getX()), std::to_string(closest_cell->getY()));

		cleanPath(pth);
		cloneMap[closest_cell->getX()][closest_cell->getY()].setType(closest_cell->getType());
		return log;
	}
}
